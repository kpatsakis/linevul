gsicc_profile_from_ps(cmm_profile_t *profile_data)
{
    switch ( profile_data->default_match ) {
        case CIE_A:
        case CIE_ABC:
        case CIE_DEF:
        case CIE_DEFG:
            return true;
        default:
            return false;
    }
}
