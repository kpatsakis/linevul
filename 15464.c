int dns_packet_append_rr(DnsPacket *p, const DnsResourceRecord *rr, const DnsAnswerFlags flags, size_t *start, size_t *rdata_start) {

        size_t saved_size, rdlength_offset, end, rdlength, rds;
        uint32_t ttl;
        int r;

        assert(p);
        assert(rr);

        saved_size = p->size;

        r = dns_packet_append_key(p, rr->key, flags, NULL);
        if (r < 0)
                goto fail;

        ttl = flags & DNS_ANSWER_GOODBYE ? 0 : rr->ttl;
        r = dns_packet_append_uint32(p, ttl, NULL);
        if (r < 0)
                goto fail;

        /* Initially we write 0 here */
        r = dns_packet_append_uint16(p, 0, &rdlength_offset);
        if (r < 0)
                goto fail;

        rds = p->size - saved_size;

        switch (rr->unparseable ? _DNS_TYPE_INVALID : rr->key->type) {

        case DNS_TYPE_SRV:
                r = dns_packet_append_uint16(p, rr->srv.priority, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint16(p, rr->srv.weight, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint16(p, rr->srv.port, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_name(p, rr->srv.name, true, false, NULL);
                break;

        case DNS_TYPE_PTR:
        case DNS_TYPE_NS:
        case DNS_TYPE_CNAME:
        case DNS_TYPE_DNAME:
                r = dns_packet_append_name(p, rr->ptr.name, true, false, NULL);
                break;

        case DNS_TYPE_HINFO:
                r = dns_packet_append_string(p, rr->hinfo.cpu, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_string(p, rr->hinfo.os, NULL);
                break;

        case DNS_TYPE_SPF: /* exactly the same as TXT */
        case DNS_TYPE_TXT:

                if (!rr->txt.items) {
                        /* RFC 6763, section 6.1 suggests to generate
                         * single empty string for an empty array. */

                        r = dns_packet_append_raw_string(p, NULL, 0, NULL);
                        if (r < 0)
                                goto fail;
                } else {
                        DnsTxtItem *i;

                        LIST_FOREACH(items, i, rr->txt.items) {
                                r = dns_packet_append_raw_string(p, i->data, i->length, NULL);
                                if (r < 0)
                                        goto fail;
                        }
                }

                r = 0;
                break;

        case DNS_TYPE_A:
                r = dns_packet_append_blob(p, &rr->a.in_addr, sizeof(struct in_addr), NULL);
                break;

        case DNS_TYPE_AAAA:
                r = dns_packet_append_blob(p, &rr->aaaa.in6_addr, sizeof(struct in6_addr), NULL);
                break;

        case DNS_TYPE_SOA:
                r = dns_packet_append_name(p, rr->soa.mname, true, false, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_name(p, rr->soa.rname, true, false, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->soa.serial, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->soa.refresh, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->soa.retry, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->soa.expire, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->soa.minimum, NULL);
                break;

        case DNS_TYPE_MX:
                r = dns_packet_append_uint16(p, rr->mx.priority, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_name(p, rr->mx.exchange, true, false, NULL);
                break;

        case DNS_TYPE_LOC:
                r = dns_packet_append_uint8(p, rr->loc.version, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->loc.size, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->loc.horiz_pre, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->loc.vert_pre, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->loc.latitude, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->loc.longitude, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->loc.altitude, NULL);
                break;

        case DNS_TYPE_DS:
                r = dns_packet_append_uint16(p, rr->ds.key_tag, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->ds.algorithm, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->ds.digest_type, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_blob(p, rr->ds.digest, rr->ds.digest_size, NULL);
                break;

        case DNS_TYPE_SSHFP:
                r = dns_packet_append_uint8(p, rr->sshfp.algorithm, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->sshfp.fptype, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_blob(p, rr->sshfp.fingerprint, rr->sshfp.fingerprint_size, NULL);
                break;

        case DNS_TYPE_DNSKEY:
                r = dns_packet_append_uint16(p, rr->dnskey.flags, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->dnskey.protocol, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->dnskey.algorithm, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_blob(p, rr->dnskey.key, rr->dnskey.key_size, NULL);
                break;

        case DNS_TYPE_RRSIG:
                r = dns_packet_append_uint16(p, rr->rrsig.type_covered, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->rrsig.algorithm, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->rrsig.labels, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->rrsig.original_ttl, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->rrsig.expiration, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint32(p, rr->rrsig.inception, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint16(p, rr->rrsig.key_tag, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_name(p, rr->rrsig.signer, false, true, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_blob(p, rr->rrsig.signature, rr->rrsig.signature_size, NULL);
                break;

        case DNS_TYPE_NSEC:
                r = dns_packet_append_name(p, rr->nsec.next_domain_name, false, false, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_types(p, rr->nsec.types, NULL);
                if (r < 0)
                        goto fail;

                break;

        case DNS_TYPE_NSEC3:
                r = dns_packet_append_uint8(p, rr->nsec3.algorithm, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->nsec3.flags, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint16(p, rr->nsec3.iterations, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->nsec3.salt_size, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_blob(p, rr->nsec3.salt, rr->nsec3.salt_size, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->nsec3.next_hashed_name_size, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_blob(p, rr->nsec3.next_hashed_name, rr->nsec3.next_hashed_name_size, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_types(p, rr->nsec3.types, NULL);
                if (r < 0)
                        goto fail;

                break;

        case DNS_TYPE_TLSA:
                r = dns_packet_append_uint8(p, rr->tlsa.cert_usage, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->tlsa.selector, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_uint8(p, rr->tlsa.matching_type, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_blob(p, rr->tlsa.data, rr->tlsa.data_size, NULL);
                break;

        case DNS_TYPE_CAA:
                r = dns_packet_append_uint8(p, rr->caa.flags, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_string(p, rr->caa.tag, NULL);
                if (r < 0)
                        goto fail;

                r = dns_packet_append_blob(p, rr->caa.value, rr->caa.value_size, NULL);
                break;

        case DNS_TYPE_OPT:
        case DNS_TYPE_OPENPGPKEY:
        case _DNS_TYPE_INVALID: /* unparseable */
        default:

                r = dns_packet_append_blob(p, rr->generic.data, rr->generic.data_size, NULL);
                break;
        }
        if (r < 0)
                goto fail;

        /* Let's calculate the actual data size and update the field */
        rdlength = p->size - rdlength_offset - sizeof(uint16_t);
        if (rdlength > 0xFFFF) {
                r = -ENOSPC;
                goto fail;
        }

        end = p->size;
        p->size = rdlength_offset;
        r = dns_packet_append_uint16(p, rdlength, NULL);
        if (r < 0)
                goto fail;
        p->size = end;

        if (start)
                *start = saved_size;

        if (rdata_start)
                *rdata_start = rds;

        return 0;

fail:
        dns_packet_truncate(p, saved_size);
        return r;
}
