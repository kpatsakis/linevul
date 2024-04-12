int wc_ecc_export_x963_ex(ecc_key* key, byte* out, word32* outLen,
                          int compressed)
{
    if (compressed == 0)
        return wc_ecc_export_x963(key, out, outLen);
#ifdef HAVE_COMP_KEY
    else
        return wc_ecc_export_x963_compressed(key, out, outLen);
#else
    return NOT_COMPILED_IN;
#endif
}
