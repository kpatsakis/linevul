gx_dc_is_pattern1_color_with_trans(const gx_device_color *pdevc)
{
    if (!(pdevc->type == &gx_dc_pattern || pdevc->type == &gx_dc_pattern_trans)) {
        return(false);
    }
    return(gx_pattern1_get_transptr(pdevc) != NULL);
}
