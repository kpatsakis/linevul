gsicc_init_iccmanager(gs_gstate * pgs)
{
    int code = 0, k;
    const char *pname;
    int namelen;
    gsicc_manager_t *iccmanager = pgs->icc_manager;
    cmm_profile_t *profile;

    for (k = 0; k < 4; k++) {
        pname = default_profile_params[k].path;
        namelen = strlen(pname);

        switch(default_profile_params[k].default_type) {
            case DEFAULT_GRAY:
                profile = iccmanager->default_gray;
                break;
            case DEFAULT_RGB:
                profile = iccmanager->default_rgb;
                break;
            case DEFAULT_CMYK:
                 profile = iccmanager->default_cmyk;
                 break;
            default:
                profile = NULL;
        }
        if (profile == NULL)
            code = gsicc_set_profile(iccmanager, pname, namelen+1,
                                     default_profile_params[k].default_type);
        if (code < 0)
            return gs_rethrow(code, "cannot find default icc profile");
    }
#if CREATE_V2_DATA
    /* Test bed for V2 creation from V4 */
    for (int j = 2; j < 3; j++)
    {
        byte *data;
        int size;

        switch (default_profile_params[j].default_type) {
        case DEFAULT_GRAY:
            profile = iccmanager->default_gray;
            break;
        case DEFAULT_RGB:
            profile = iccmanager->default_rgb;
            break;
        case DEFAULT_CMYK:
            profile = iccmanager->default_cmyk;
            break;
        default:
            profile = NULL;
        }
        gsicc_initialize_default_profile(profile);
        data = gsicc_create_getv2buffer(pgs, profile, &size);
    }
#endif
    return 0;
}
