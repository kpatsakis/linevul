WORD32 ih264d_do_mmco_for_gaps(dpb_manager_t *ps_dpb_mgr,
                             UWORD8 u1_num_ref_frames /*!< num_ref_frames from active SeqParSet*/
 )
{
 struct dpb_info_t *ps_next_dpb;
    UWORD8 u1_num_gaps;
    UWORD8 u1_st_ref_bufs, u1_lt_ref_bufs, u1_del_node;
    WORD8 i;
    WORD32 i4_frame_gaps = 1;
    WORD32 ret;

    u1_st_ref_bufs = ps_dpb_mgr->u1_num_st_ref_bufs;
    u1_lt_ref_bufs = ps_dpb_mgr->u1_num_lt_ref_bufs;

 while(1)
 {
        u1_num_gaps = ps_dpb_mgr->u1_num_gaps;
 if((u1_st_ref_bufs + u1_lt_ref_bufs + u1_num_gaps + i4_frame_gaps)
 > u1_num_ref_frames)
 {
 if(0 == (u1_st_ref_bufs + u1_num_gaps))
 {
                i4_frame_gaps = 0;
                ps_dpb_mgr->u1_num_gaps = (u1_num_ref_frames
 - u1_lt_ref_bufs);
 }
 else
 {
                u1_del_node = 1;
                ps_next_dpb = ps_dpb_mgr->ps_dpb_st_head;

 if(u1_st_ref_bufs > 1)
 {
 for(i = 1; i < (u1_st_ref_bufs - 1); i++)
 {
 if(ps_next_dpb == NULL)
 {
                            UWORD32 i4_error_code;
                            i4_error_code = ERROR_DBP_MANAGER_T;
 return i4_error_code;
 }
                        ps_next_dpb = ps_next_dpb->ps_prev_short;
 }

 if(ps_next_dpb->ps_prev_short->ps_prev_short != NULL)
 {
 return ERROR_DBP_MANAGER_T;
 }

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
                        u1_st_ref_bufs--;
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
 else
 {
 if(u1_st_ref_bufs)
 {
 if(u1_num_gaps)
 {
                            ret = ih264d_delete_gap_frm_sliding(ps_dpb_mgr,
                                                                ps_next_dpb->i4_frame_num,
 &u1_del_node);
 if(ret != OK)
 return ret;
 }

 if(u1_del_node)
 {
                            u1_st_ref_bufs--;
                            ps_next_dpb->u1_used_as_ref = FALSE;
                            ps_next_dpb->s_top_field.u1_reference_info =
                                            UNUSED_FOR_REF;
                            ps_next_dpb->s_bot_field.u1_reference_info =
                                            UNUSED_FOR_REF;
                            ih264d_free_ref_pic_mv_bufs(ps_dpb_mgr->pv_codec_handle,
                                                        ps_next_dpb->u1_buf_id);
                            ps_next_dpb->ps_pic_buf = NULL;
                            ps_next_dpb = NULL;
                            ps_dpb_mgr->ps_dpb_st_head = NULL;
                            ps_dpb_mgr->u1_num_st_ref_bufs = u1_st_ref_bufs;
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
 return ERROR_DBP_MANAGER_T;
 }
 }
 }
 }
 }
 else
 {
            ps_dpb_mgr->u1_num_gaps += i4_frame_gaps;
 break;
 }
 }

    ps_dpb_mgr->u1_num_st_ref_bufs = u1_st_ref_bufs;

 return OK;
}
