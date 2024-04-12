pdf14_push_text_group(gx_device *dev, gs_gstate *pgs, gx_path *path,
    const gx_clip_path *pcpath, gs_blend_mode_t blend_mode, float opacity,
    bool is_clist)
{
    int code;
    gs_transparency_group_params_t params = { 0 };
    gs_rect bbox = { 0 }; /* Bounding box is set by parent */
    pdf14_clist_device * pdev = (pdf14_clist_device *)dev;

    /* Push a non-isolated knock-out group making sure the opacity and blend
       mode are correct */
    params.Isolated = false;
    params.Knockout = true;
    params.text_group = PDF14_TEXTGROUP_BT_PUSHED;
    gs_setopacityalpha(pgs, 1.0);
    gs_setblendmode(pgs, BLEND_MODE_Normal);
    if (is_clist) {
        code = pdf14_clist_update_params(pdev, pgs, false, NULL);
        if (code < 0)
            return code;
    }
    code = gs_begin_transparency_group(pgs, &params, &bbox);
    if (code < 0)
        return code;
    gs_setopacityalpha(pgs, opacity);
    gs_setblendmode(pgs, blend_mode);
    if (is_clist)
        code = pdf14_clist_update_params(pdev, pgs, false, NULL);
    return code;
}
