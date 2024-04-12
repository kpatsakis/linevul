WORD32 ih264d_do_mmco_buffer(dpb_commands_t *ps_dpb_cmds,
 dpb_manager_t *ps_dpb_mgr,
                          UWORD8 u1_numRef_frames_for_seq, /*!< num_ref_frames from active SeqParSet*/
                          UWORD32 u4_cur_pic_num,
                          UWORD32 u2_u4_max_pic_num_minus1,
                          UWORD8 u1_nal_unit_type,
 struct pic_buffer_t *ps_pic_buf,
                          UWORD8 u1_buf_id,
                          UWORD8 u1_fld_pic_flag,
                          UWORD8 u1_curr_pic_in_err)
{
    WORD32 i;
    UWORD8 u1_buf_mode, u1_marked_lt;
 struct dpb_info_t *ps_next_dpb;
    UWORD8 u1_num_gaps;
    UWORD8 u1_del_node = 1;
    UWORD8 u1_insert_st_pic = 1;
    WORD32 ret;
    UNUSED(u1_nal_unit_type);
    UNUSED(u2_u4_max_pic_num_minus1);
    u1_buf_mode = ps_dpb_cmds->u1_buf_mode; //0 - sliding window; 1 - Adaptive
    u1_marked_lt = 0;
    u1_num_gaps = ps_dpb_mgr->u1_num_gaps;

 if(!u1_buf_mode)
 {
 if((ps_dpb_mgr->u1_num_st_ref_bufs
 + ps_dpb_mgr->u1_num_lt_ref_bufs + u1_num_gaps)
 == u1_numRef_frames_for_seq)
 {
            UWORD8 u1_new_node_flag = 1;
 if((0 == ps_dpb_mgr->u1_num_st_ref_bufs) && (0 == u1_num_gaps))
 {
                UWORD32 i4_error_code;
                i4_error_code = ERROR_DBP_MANAGER_T;
 return i4_error_code;
 }

            ps_next_dpb = ps_dpb_mgr->ps_dpb_st_head;

 if(ps_dpb_mgr->u1_num_st_ref_bufs > 1)
 {
 if(ps_next_dpb->i4_frame_num == (WORD32)u4_cur_pic_num)
 {
 /* Incase of  filed pictures top_field has been allocated   */
 /* picture buffer and complementary bottom field pair comes */
 /* then the sliding window mechanism should not allocate a  */
 /* new node                                                 */
                    u1_new_node_flag = 0;
 }

 for(i = 1; i < (ps_dpb_mgr->u1_num_st_ref_bufs - 1); i++)
 {
 if(ps_next_dpb == NULL)
 {
                        UWORD32 i4_error_code;
                        i4_error_code = ERROR_DBP_MANAGER_T;
 return i4_error_code;
 }
 if(ps_next_dpb->i4_frame_num == (WORD32)u4_cur_pic_num)
 {
 /* Incase of  field pictures top_field has been allocated   */
 /* picture buffer and complementary bottom field pair comes */
 /* then the sliding window mechanism should not allocate a  */
 /* new node                                                 */
                        u1_new_node_flag = 0;
 }
                    ps_next_dpb = ps_next_dpb->ps_prev_short;
 }

 if(ps_next_dpb->ps_prev_short->ps_prev_short != NULL)
 {
                    UWORD32 i4_error_code;
                    i4_error_code = ERROR_DBP_MANAGER_T;
 return i4_error_code;
 }

 if(u1_new_node_flag)
 {
 if(u1_num_gaps)
 {
                        ret = ih264d_delete_gap_frm_sliding(ps_dpb_mgr,
                                                            ps_next_dpb->ps_prev_short->i4_frame_num,
 &u1_del_node);
 if(ret != OK)
 return ret;
 }

 if(u1_del_node)
 {
                        ps_dpb_mgr->u1_num_st_ref_bufs--;
                        ps_next_dpb->ps_prev_short->u1_used_as_ref =
                                        UNUSED_FOR_REF;
                        ps_next_dpb->ps_prev_short->s_top_field.u1_reference_info =
                                        UNUSED_FOR_REF;
                        ps_next_dpb->ps_prev_short->s_bot_field.u1_reference_info =
                                        UNUSED_FOR_REF;
                        ih264d_free_ref_pic_mv_bufs(ps_dpb_mgr->pv_codec_handle,
                                                    ps_next_dpb->ps_prev_short->u1_buf_id);
                        ps_next_dpb->ps_prev_short->ps_pic_buf = NULL;
                        ps_next_dpb->ps_prev_short = NULL;
 }
 }
 }
 else
 {
 if(ps_dpb_mgr->u1_num_st_ref_bufs)
 {
                    ret = ih264d_delete_gap_frm_sliding(ps_dpb_mgr,
                                                       ps_next_dpb->i4_frame_num,
 &u1_del_node);
 if(ret != OK)
 return ret;
 if((ps_next_dpb->i4_frame_num != (WORD32)u4_cur_pic_num)
 && u1_del_node)
 {
                        ps_dpb_mgr->u1_num_st_ref_bufs--;
                        ps_next_dpb->u1_used_as_ref = FALSE;
                        ps_next_dpb->s_top_field.u1_reference_info =
                                        UNUSED_FOR_REF;
                        ps_next_dpb->s_bot_field.u1_reference_info =
                                        UNUSED_FOR_REF;
                        ih264d_free_ref_pic_mv_bufs(ps_dpb_mgr->pv_codec_handle,
                                                    ps_next_dpb->u1_buf_id);
                        ps_next_dpb->ps_pic_buf = NULL;
                        ps_next_dpb->ps_prev_short = NULL;
                        ps_dpb_mgr->ps_dpb_st_head = NULL;
                        ps_next_dpb = NULL;
 }
 else if(ps_next_dpb->i4_frame_num == (WORD32)u4_cur_pic_num)
 {
 if(u1_curr_pic_in_err)
 {
                            u1_insert_st_pic = 0;
 }
 else if(ps_dpb_mgr->u1_num_st_ref_bufs > 0)
 {
                            ps_dpb_mgr->u1_num_st_ref_bufs--;
                            ps_next_dpb->u1_used_as_ref = FALSE;
                            ps_next_dpb->s_top_field.u1_reference_info =
                                            UNUSED_FOR_REF;
                            ps_next_dpb->s_bot_field.u1_reference_info =
                                            UNUSED_FOR_REF;
                            ih264d_free_ref_pic_mv_bufs(ps_dpb_mgr->pv_codec_handle,
                                                        ps_next_dpb->u1_buf_id);
                            ps_next_dpb->ps_pic_buf = NULL;
                            ps_next_dpb = NULL;
 }
 }
 }
 else
 {
                    ret = ih264d_delete_gap_frm_sliding(ps_dpb_mgr,
                                                        INVALID_FRAME_NUM,
 &u1_del_node);
 if(ret != OK)
 return ret;
 if(u1_del_node)
 {
                        UWORD32 i4_error_code;
                        i4_error_code = ERROR_DBP_MANAGER_T;
 return i4_error_code;
 }
 }
 }
 }
 }
 else
 {
        UWORD32 u4_mmco;
        UWORD32 u4_diff_pic_num;
        WORD32 i4_pic_num;
        UWORD32 u4_lt_idx;
        WORD32 j;
 struct MMCParams *ps_mmc_params;

 for(j = 0; j < ps_dpb_cmds->u1_num_of_commands; j++)
 {
            ps_mmc_params = &ps_dpb_cmds->as_mmc_params[j];
            u4_mmco = ps_mmc_params->u4_mmco; //Get MMCO

 switch(u4_mmco)
 {
 case MARK_ST_PICNUM_AS_NONREF:
 {

 {
                        UWORD32 i4_cur_pic_num = u4_cur_pic_num;
                        u4_diff_pic_num = ps_mmc_params->u4_diff_pic_num; //Get absDiffPicnumMinus1
 if(u1_fld_pic_flag)
                            i4_cur_pic_num = i4_cur_pic_num * 2 + 1;
                        i4_pic_num = i4_cur_pic_num - (u4_diff_pic_num + 1);
 }

 if(ps_dpb_mgr->u1_num_st_ref_bufs > 0)
 {
                        ret = ih264d_delete_st_node_or_make_lt(ps_dpb_mgr,
                                                               i4_pic_num,
                                                               MAX_REF_BUFS + 1,
                                                               u1_fld_pic_flag);
 if(ret != OK)
 return ret;
 }
 else
 {
                        UWORD8 u1_dummy;
                        ret = ih264d_delete_gap_frm_mmco(ps_dpb_mgr, i4_pic_num, &u1_dummy);
 if(ret != OK)
 return ret;
 }
 break;
 }
 case MARK_LT_INDEX_AS_NONREF:
 {
                    WORD32 i4_status;
                    u4_lt_idx = ps_mmc_params->u4_lt_idx; //Get long term index
                    ret = ih264d_delete_lt_node(ps_dpb_mgr,
                                                u4_lt_idx,
                                                u1_fld_pic_flag,
 0, &i4_status);
 if(ret != OK)
 return ret;
 if(i4_status)
 {
                        UWORD32 i4_error_code;
                        i4_error_code = ERROR_DBP_MANAGER_T;
 return i4_error_code;
 }
 break;
 }

 case MARK_ST_PICNUM_AS_LT_INDEX:
 {
 {
                        UWORD32 i4_cur_pic_num = u4_cur_pic_num;
                        u4_diff_pic_num = ps_mmc_params->u4_diff_pic_num; //Get absDiffPicnumMinus1
 if(u1_fld_pic_flag)
                            i4_cur_pic_num = i4_cur_pic_num * 2 + 1;

                        i4_pic_num = i4_cur_pic_num - (u4_diff_pic_num + 1);
 }

                    u4_lt_idx = ps_mmc_params->u4_lt_idx; //Get long term index
 if(ps_dpb_mgr->u1_num_st_ref_bufs > 0)
 {
                        ret = ih264d_delete_st_node_or_make_lt(ps_dpb_mgr,
                                                               i4_pic_num, u4_lt_idx,
                                                               u1_fld_pic_flag);
 if(ret != OK)
 return ret;
 }
 break;
 }
 case SET_MAX_LT_INDEX:
 {
                    UWORD8 uc_numLT = ps_dpb_mgr->u1_num_lt_ref_bufs;
                    u4_lt_idx = ps_mmc_params->u4_max_lt_idx_plus1; //Get Max_long_term_index_plus1
 if(u4_lt_idx < ps_dpb_mgr->u1_max_lt_pic_idx_plus1
 && uc_numLT > 0)
 {
 struct dpb_info_t *ps_nxtDPB;
                        ps_nxtDPB = ps_dpb_mgr->ps_dpb_ht_head;
                        ps_next_dpb = ps_nxtDPB->ps_prev_long;
 if(ps_nxtDPB->u1_lt_idx >= u4_lt_idx)
 {
                            i = 0;
                            ps_dpb_mgr->ps_dpb_ht_head = NULL;
 }
 else
 {
 for(i = 1; i < uc_numLT; i++)
 {
 if(ps_next_dpb->u1_lt_idx >= u4_lt_idx)
 break;
                                ps_nxtDPB = ps_next_dpb;
                                ps_next_dpb = ps_next_dpb->ps_prev_long;
 }
                            ps_nxtDPB->ps_prev_long = NULL; //Terminate the link of the closest LTIndex that is <=Max
 }
                        ps_dpb_mgr->u1_num_lt_ref_bufs = i;
 if(i == 0)
                            ps_next_dpb = ps_nxtDPB;

 for(; i < uc_numLT; i++)
 {
                            ps_nxtDPB = ps_next_dpb;
                            ps_nxtDPB->u1_lt_idx = MAX_REF_BUFS + 1;
                            ps_nxtDPB->u1_used_as_ref = UNUSED_FOR_REF;
                            ps_nxtDPB->s_top_field.u1_reference_info =
                                            UNUSED_FOR_REF;
                            ps_nxtDPB->s_bot_field.u1_reference_info =
                                            UNUSED_FOR_REF;

                            ps_nxtDPB->ps_pic_buf = NULL;
                            ih264d_free_ref_pic_mv_bufs(ps_dpb_mgr->pv_codec_handle,
                                                        ps_nxtDPB->u1_buf_id);
                            ps_next_dpb = ps_nxtDPB->ps_prev_long;
                            ps_nxtDPB->ps_prev_long = NULL;
 }
 }
                    ps_dpb_mgr->u1_max_lt_pic_idx_plus1 = u4_lt_idx;

 break;
 }
 case SET_LT_INDEX:
 {
                    u4_lt_idx = ps_mmc_params->u4_lt_idx; //Get long term index
                    ret = ih264d_insert_st_node(ps_dpb_mgr, ps_pic_buf, u1_buf_id,
                                          u4_cur_pic_num);
 if(ret != OK)
 return ret;
                    ret = ih264d_delete_st_node_or_make_lt(ps_dpb_mgr,
                                                     u4_cur_pic_num, u4_lt_idx,
                                                     u1_fld_pic_flag);
 if(ret != OK)
 return ret;
                    u1_marked_lt = 1;
 break;
 }

 default:
 break;
 }
 if(u4_mmco == RESET_REF_PICTURES || u4_mmco == RESET_ALL_PICTURES)
 {
                ih264d_reset_ref_bufs(ps_dpb_mgr);
                u4_cur_pic_num = 0;
 }
 }
 }
 if(!u1_marked_lt && u1_insert_st_pic)
 {
        ret = ih264d_insert_st_node(ps_dpb_mgr, ps_pic_buf, u1_buf_id,
                              u4_cur_pic_num);
 if(ret != OK)
 return ret;
 }
 return OK;
}
