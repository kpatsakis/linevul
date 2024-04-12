void _out_dns_mark_bad(conn_t out) {
    if (out->s2s->dns_bad_timeout > 0) {
        dnsres_t bad;
        char *ipport;

        /* mark this host as bad */
        ipport = dns_make_ipport(out->ip, out->port);
        bad = xhash_get(out->s2s->dns_bad, ipport);
        if (bad == NULL) {
            bad = (dnsres_t) calloc(1, sizeof(struct dnsres_st));
            bad->key = ipport;
            xhash_put(out->s2s->dns_bad, ipport, bad);
        }
        bad->expiry = time(NULL) + out->s2s->dns_bad_timeout;
    }
}
