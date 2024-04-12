static struct VP8D_COMP * create_decompressor(VP8D_CONFIG *oxcf)
{
    VP8D_COMP *pbi = vpx_memalign(32, sizeof(VP8D_COMP));

 if (!pbi)
 return NULL;

    memset(pbi, 0, sizeof(VP8D_COMP));

 if (setjmp(pbi->common.error.jmp))
 {
        pbi->common.error.setjmp = 0;
        remove_decompressor(pbi);
 return 0;
 }

    pbi->common.error.setjmp = 1;

    vp8_create_common(&pbi->common);

    pbi->common.current_video_frame = 0;
    pbi->ready_for_new_data = 1;

 /* vp8cx_init_de_quantizer() is first called here. Add check in frame_init_dequantizer() to avoid
     *  unnecessary calling of vp8cx_init_de_quantizer() for every frame.
     */
    vp8cx_init_de_quantizer(pbi);

    vp8_loop_filter_init(&pbi->common);

    pbi->common.error.setjmp = 0;

#if CONFIG_ERROR_CONCEALMENT
    pbi->ec_enabled = oxcf->error_concealment;
    pbi->overlaps = NULL;
#else
 (void)oxcf;
    pbi->ec_enabled = 0;
#endif
 /* Error concealment is activated after a key frame has been
     * decoded without errors when error concealment is enabled.
     */
    pbi->ec_active = 0;

    pbi->decoded_key_frame = 0;

 /* Independent partitions is activated when a frame updates the
     * token probability table to have equal probabilities over the
     * PREV_COEF context.
     */
    pbi->independent_partitions = 0;

    vp8_setup_block_dptrs(&pbi->mb);

    once(initialize_dec);

 return pbi;
}
