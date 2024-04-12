pdf14_fill_path(gx_device *dev,	const gs_gstate *pgs,
                           gx_path *ppath, const gx_fill_params *params,
                           const gx_drawing_color *pdcolor,
                           const gx_clip_path *pcpath)
{
    gs_gstate new_pgs = *pgs;
    int code;
    gs_pattern2_instance_t *pinst = NULL;

    if (pdcolor == NULL)
       return_error(gs_error_unknownerror);	/* color must be defined */
    if (gx_dc_is_pattern1_color(pdcolor)){
        if( gx_pattern1_get_transptr(pdcolor) != NULL ||
            gx_pattern1_clist_has_trans(pdcolor) ){
            /* In this case, we need to push a transparency group
               and tile the pattern color, which is stored in
               a pdf14 device buffer in the ctile object memember
               variable ttrans */
#if RAW_DUMP
            /* Since we do not get a put_image to view what
               we have do it now */
            if (gx_pattern1_get_transptr(pdcolor) != NULL) {
                pdf14_device * ppatdev14 =
                                pdcolor->colors.pattern.p_tile->ttrans->pdev14;
                if (ppatdev14 != NULL) {  /* can occur during clist reading */
                    byte *buf_ptr = ppatdev14->ctx->stack->data  +
                        ppatdev14->ctx->stack->rect.p.y *
                        ppatdev14->ctx->stack->rowstride +
                        ppatdev14->ctx->stack->rect.p.x;
                    dump_raw_buffer(ppatdev14->ctx->stack->rect.q.y -
                                    ppatdev14->ctx->stack->rect.p.y,
                                    ppatdev14->ctx->stack->rect.q.x -
                                    ppatdev14->ctx->stack->rect.p.x,
                                    ppatdev14->ctx->stack->n_planes,
                                    ppatdev14->ctx->stack->planestride,
                                    ppatdev14->ctx->stack->rowstride,
                                    "Pattern_Fill",buf_ptr);
                    global_index++;
                } else {
                     gx_pattern_trans_t *patt_trans =
                                        pdcolor->colors.pattern.p_tile->ttrans;
                     dump_raw_buffer(patt_trans->rect.q.y-patt_trans->rect.p.y,
                                patt_trans->rect.q.x-patt_trans->rect.p.x,
                                                patt_trans->n_chan,
                                patt_trans->planestride, patt_trans->rowstride,
                                "Pattern_Fill_clist", patt_trans->transbytes +
                                patt_trans->rect.p.y * patt_trans->rowstride +
                                patt_trans->rect.p.x);
                    global_index++;
                }
            }
#endif
            code = pdf14_tile_pattern_fill(dev, &new_pgs, ppath,
                params, pdcolor, pcpath);
            new_pgs.trans_device = NULL;
            new_pgs.has_transparency = false;
            return code;
        }
    }
    if (gx_dc_is_pattern2_color(pdcolor)) {
        pinst =
            (gs_pattern2_instance_t *)pdcolor->ccolor.pattern;
           pinst->saved->has_transparency = true;
           /* The transparency color space operations are driven
              by the pdf14 clist writer device.  */
           pinst->saved->trans_device = dev;
    }
    update_lop_for_pdf14(&new_pgs, pdcolor);
    pdf14_set_marking_params(dev, pgs);
    new_pgs.trans_device = dev;
    new_pgs.has_transparency = true;
    code = gx_default_fill_path(dev, &new_pgs, ppath, params, pdcolor, pcpath);
    new_pgs.trans_device = NULL;
    new_pgs.has_transparency = false;
    if (pinst != NULL){
        pinst->saved->trans_device = NULL;
    }
    return code;
}
