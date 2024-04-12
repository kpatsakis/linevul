IHEVCD_ERROR_T ihevcd_parse_mastering_disp_params_sei(codec_t *ps_codec)
{
 parse_ctxt_t *ps_parse = &ps_codec->s_parse;
 bitstrm_t *ps_bitstrm = &ps_parse->s_bitstrm;
    UWORD32 value;
 mastering_dis_col_vol_sei_params_t *ps_mastering_dis_col_vol;
    WORD32 i;

    ps_parse->s_sei_params.i4_sei_mastering_disp_colour_vol_params_present_flags = 1;

    ps_mastering_dis_col_vol = &ps_parse->s_sei_params.s_mastering_dis_col_vol_sei_params;

 for(i = 0; i < 3; i++)
 {
        BITS_PARSE("display_primaries_x[c]", value, ps_bitstrm, 16);
        ps_mastering_dis_col_vol->au2_display_primaries_x[i] = value;

        BITS_PARSE("display_primaries_y[c]", value, ps_bitstrm, 16);
        ps_mastering_dis_col_vol->au2_display_primaries_y[i] = value;
 }

    BITS_PARSE("white_point_x", value, ps_bitstrm, 16);
    ps_mastering_dis_col_vol->u2_white_point_x = value;

    BITS_PARSE("white_point_y", value, ps_bitstrm, 16);
    ps_mastering_dis_col_vol->u2_white_point_y = value;

    BITS_PARSE("max_display_mastering_luminance", value, ps_bitstrm, 32);
    ps_mastering_dis_col_vol->u4_max_display_mastering_luminance = value;

    BITS_PARSE("min_display_mastering_luminance", value, ps_bitstrm, 32);
    ps_mastering_dis_col_vol->u4_min_display_mastering_luminance = value;

 return (IHEVCD_ERROR_T)IHEVCD_SUCCESS;
}
