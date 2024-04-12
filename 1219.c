gsicc_profile_reference(cmm_profile_t *icc_profile, int delta)
{
    if (icc_profile != NULL)
        rc_adjust(icc_profile, delta, "gsicc_profile_reference");
}
