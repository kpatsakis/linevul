static int asn1_d2i_ex_primitive(ASN1_VALUE **pval,
                                 const unsigned char **in, long inlen,
                                 const ASN1_ITEM *it,
                                 int tag, int aclass, char opt, ASN1_TLC *ctx)
{
    int ret = 0, utype;
    long plen;
    char cst, inf, free_cont = 0;
    const unsigned char *p;
    BUF_MEM buf;
    const unsigned char *cont = NULL;
    long len;
    if (!pval) {
        ASN1err(ASN1_F_ASN1_D2I_EX_PRIMITIVE, ASN1_R_ILLEGAL_NULL);
        return 0;               /* Should never happen */
    }

    if (it->itype == ASN1_ITYPE_MSTRING) {
        utype = tag;
        tag = -1;
    } else
        utype = it->utype;

    if (utype == V_ASN1_ANY) {
        /* If type is ANY need to figure out type from tag */
        unsigned char oclass;
        if (tag >= 0) {
            ASN1err(ASN1_F_ASN1_D2I_EX_PRIMITIVE, ASN1_R_ILLEGAL_TAGGED_ANY);
            return 0;
        }
        if (opt) {
            ASN1err(ASN1_F_ASN1_D2I_EX_PRIMITIVE,
                    ASN1_R_ILLEGAL_OPTIONAL_ANY);
            return 0;
        }
        p = *in;
        ret = asn1_check_tlen(NULL, &utype, &oclass, NULL, NULL,
                              &p, inlen, -1, 0, 0, ctx);
        if (!ret) {
            ASN1err(ASN1_F_ASN1_D2I_EX_PRIMITIVE, ERR_R_NESTED_ASN1_ERROR);
            return 0;
        }
        if (oclass != V_ASN1_UNIVERSAL)
            utype = V_ASN1_OTHER;
    }
    if (tag == -1) {
        tag = utype;
        aclass = V_ASN1_UNIVERSAL;
    }
    p = *in;
    /* Check header */
    ret = asn1_check_tlen(&plen, NULL, NULL, &inf, &cst,
                          &p, inlen, tag, aclass, opt, ctx);
    if (!ret) {
        ASN1err(ASN1_F_ASN1_D2I_EX_PRIMITIVE, ERR_R_NESTED_ASN1_ERROR);
        return 0;
    } else if (ret == -1)
        return -1;
    ret = 0;
    /* SEQUENCE, SET and "OTHER" are left in encoded form */
    if ((utype == V_ASN1_SEQUENCE)
        || (utype == V_ASN1_SET) || (utype == V_ASN1_OTHER)) {
        /*
         * Clear context cache for type OTHER because the auto clear when we
         * have a exact match wont work
         */
        if (utype == V_ASN1_OTHER) {
            asn1_tlc_clear(ctx);
        }
        /* SEQUENCE and SET must be constructed */
        else if (!cst) {
            ASN1err(ASN1_F_ASN1_D2I_EX_PRIMITIVE,
                    ASN1_R_TYPE_NOT_CONSTRUCTED);
            return 0;
        }

        cont = *in;
        /* If indefinite length constructed find the real end */
        if (inf) {
            if (!asn1_find_end(&p, plen, inf))
                goto err;
            len = p - cont;
        } else {
            len = p - cont + plen;
            p += plen;
            buf.data = NULL;
        }
    } else if (cst) {
        if (utype == V_ASN1_NULL || utype == V_ASN1_BOOLEAN
            || utype == V_ASN1_OBJECT || utype == V_ASN1_INTEGER
            || utype == V_ASN1_ENUMERATED) {
            ASN1err(ASN1_F_ASN1_D2I_EX_PRIMITIVE, ASN1_R_TYPE_NOT_PRIMITIVE);
            return 0;
        }
        buf.length = 0;
        buf.max = 0;
        buf.data = NULL;
        /*
         * Should really check the internal tags are correct but some things
         * may get this wrong. The relevant specs say that constructed string
         * types should be OCTET STRINGs internally irrespective of the type.
         * So instead just check for UNIVERSAL class and ignore the tag.
         */
        if (!asn1_collect(&buf, &p, plen, inf, -1, V_ASN1_UNIVERSAL, 0)) {
            free_cont = 1;
            goto err;
        }
        len = buf.length;
        /* Append a final null to string */
        if (!BUF_MEM_grow_clean(&buf, len + 1)) {
            ASN1err(ASN1_F_ASN1_D2I_EX_PRIMITIVE, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        buf.data[len] = 0;
        cont = (const unsigned char *)buf.data;
        free_cont = 1;
    } else {
        cont = p;
        len = plen;
        p += plen;
    }

    /* We now have content length and type: translate into a structure */
    if (!asn1_ex_c2i(pval, cont, len, utype, &free_cont, it))
        goto err;

    *in = p;
    ret = 1;
 err:
    if (free_cont && buf.data)
        OPENSSL_free(buf.data);
    return ret;
}
