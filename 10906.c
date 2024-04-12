int wc_ecc_get_oid(word32 oidSum, const byte** oid, word32* oidSz)
{
    int x;

    if (oidSum == 0) {
        return BAD_FUNC_ARG;
    }

    /* find matching OID sum (based on encoded value) */
    for (x = 0; ecc_sets[x].size != 0; x++) {
        if (ecc_sets[x].oidSum == oidSum) {
            int ret = 0;
        #ifdef HAVE_OID_ENCODING
            /* check cache */
            oid_cache_t* o = &ecc_oid_cache[x];
            if (o->oidSz == 0) {
                o->oidSz = sizeof(o->oid);
                ret = EncodeObjectId(ecc_sets[x].oid, ecc_sets[x].oidSz,
                                                            o->oid, &o->oidSz);
            }
            if (oidSz) {
                *oidSz = o->oidSz;
            }
            if (oid) {
                *oid = o->oid;
            }
        #else
            if (oidSz) {
                *oidSz = ecc_sets[x].oidSz;
            }
            if (oid) {
                *oid = ecc_sets[x].oid;
            }
        #endif
            /* on success return curve id */
            if (ret == 0) {
                ret = ecc_sets[x].id;
            }
            return ret;
        }
    }

    return NOT_COMPILED_IN;
}
