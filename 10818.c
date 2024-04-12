WORD32 ih264d_ref_idx_reordering(dec_struct_t *ps_dec, UWORD8 uc_lx)
{
 dpb_manager_t *ps_dpb_mgr = ps_dec->ps_dpb_mgr;
    UWORD16 u4_cur_pic_num = ps_dec->ps_cur_slice->u2_frame_num;
 /*< Maximum Picture Number Minus 1 */
    UWORD16 ui_max_frame_num =
                    ps_dec->ps_cur_sps->u2_u4_max_pic_num_minus1 + 1;

    WORD32 i;
    UWORD32 ui_remapIdc, ui_nextUev;
    WORD16 u2_pred_frame_num = u4_cur_pic_num;
    WORD32 i_temp;
    UWORD16 u2_def_mod_flag = 0; /* Flag to keep track of which indices have been remapped */
    UWORD8 modCount = 0;
    UWORD32 *pu4_bitstrm_buf = ps_dec->ps_bitstrm->pu4_buffer;
    UWORD32 *pu4_bitstrm_ofst = &ps_dec->ps_bitstrm->u4_ofst;
 dec_slice_params_t *ps_cur_slice = ps_dec->ps_cur_slice;
    UWORD8 u1_field_pic_flag = ps_cur_slice->u1_field_pic_flag;

 if(u1_field_pic_flag)
 {
        u4_cur_pic_num = u4_cur_pic_num * 2 + 1;
        ui_max_frame_num = ui_max_frame_num * 2;
 }

    u2_pred_frame_num = u4_cur_pic_num;

    ui_remapIdc = ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);

 while(ui_remapIdc != 3)
 {
        ui_nextUev = ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
 if(ui_remapIdc != 2)
 {
            ui_nextUev = ui_nextUev + 1;
 if(ui_remapIdc == 0)
 {
                i_temp = u2_pred_frame_num - ui_nextUev;
 if(i_temp < 0)
                    i_temp += ui_max_frame_num;
 }
 else
 {
                i_temp = u2_pred_frame_num + ui_nextUev;
 if(i_temp >= ui_max_frame_num)
                    i_temp -= ui_max_frame_num;
 }
 /* Find the dpb with the matching picNum (picNum==frameNum for framePic) */

 if(i_temp > u4_cur_pic_num)
                i_temp = i_temp - ui_max_frame_num;

 for(i = 0; i < (ps_cur_slice->u1_initial_list_size[uc_lx]); i++)
 {
 if(ps_dpb_mgr->ps_init_dpb[uc_lx][i]->i4_pic_num == i_temp)
 break;
 }
 if(i == (ps_cur_slice->u1_initial_list_size[uc_lx]))
 {
                UWORD32 i4_error_code;
                i4_error_code = ERROR_DBP_MANAGER_T;
 return i4_error_code;
 }

            u2_def_mod_flag |= (1 << i);
            ps_dpb_mgr->ps_mod_dpb[uc_lx][modCount++] =
                            ps_dpb_mgr->ps_init_dpb[uc_lx][i];
            u2_pred_frame_num = i_temp; //update predictor to be the picNum just obtained
 }
 else //2
 {
            UWORD8 u1_lt_idx = (UWORD8)ui_nextUev;

 for(i = 0; i < (ps_cur_slice->u1_initial_list_size[uc_lx]); i++)
 {
 if(!ps_dpb_mgr->ps_init_dpb[uc_lx][i]->u1_is_short)
 {
 if(ps_dpb_mgr->ps_init_dpb[uc_lx][i]->u1_long_term_pic_num
 == u1_lt_idx)
 break;
 }
 }
 if(i == (ps_cur_slice->u1_initial_list_size[uc_lx]))
 {
                UWORD32 i4_error_code;
                i4_error_code = ERROR_DBP_MANAGER_T;
 return i4_error_code;
 }

            u2_def_mod_flag |= (1 << i);
            ps_dpb_mgr->ps_mod_dpb[uc_lx][modCount++] =
                            ps_dpb_mgr->ps_init_dpb[uc_lx][i];
 }

        ui_remapIdc = ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
 /* Get the remapping_idc - 0/1/2/3 */
 }

 for(i = 0; i < (ps_cur_slice->u1_num_ref_idx_lx_active[uc_lx]); i++)
 {
 if(!(u2_def_mod_flag & (1 << i)))
            ps_dpb_mgr->ps_mod_dpb[uc_lx][modCount++] =
                            ps_dpb_mgr->ps_init_dpb[uc_lx][i];
 }
 return OK;
}
