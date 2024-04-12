void ih264d_update_nnz_for_skipmb(dec_struct_t * ps_dec,
 dec_mb_info_t * ps_cur_mb_info,
                                  UWORD8 u1_entrpy)
{
    UWORD32 *pu4_buf;
    UWORD8 *pu1_buf;
    UNUSED(u1_entrpy);
    pu1_buf = ps_dec->pu1_left_nnz_y;
    pu4_buf = (UWORD32 *)pu1_buf;
 *pu4_buf = 0;
    pu1_buf = ps_dec->pu1_left_nnz_uv;
    pu4_buf = (UWORD32 *)pu1_buf;
 *pu4_buf = 0;
    pu1_buf = ps_cur_mb_info->ps_curmb->pu1_nnz_y;
    pu4_buf = (UWORD32 *)pu1_buf;
 *pu4_buf = 0;
    pu1_buf = ps_cur_mb_info->ps_curmb->pu1_nnz_uv;
    pu4_buf = (UWORD32 *)pu1_buf;
 *pu4_buf = 0;
    ps_cur_mb_info->ps_curmb->u2_luma_csbp = 0;
    ps_cur_mb_info->u2_luma_csbp = 0;
    ps_cur_mb_info->u2_chroma_csbp = 0;
}
