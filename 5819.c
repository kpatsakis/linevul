WORD32 ih264d_delete_lt_node(dpb_manager_t *ps_dpb_mgr,
                             UWORD32 u4_lt_idx,
                             UWORD8 u1_fld_pic_flag,
 struct dpb_info_t *ps_lt_node_to_insert,
                             WORD32 *pi4_status)
{
 *pi4_status = 0;
 if(ps_dpb_mgr->u1_num_lt_ref_bufs > 0)
 {
        WORD32 i;
 struct dpb_info_t *ps_next_dpb;
 /* ps_unmark_node points to the node to be removed */
 /* from long term list.                            */
 struct dpb_info_t *ps_unmark_node;
        ps_next_dpb = ps_dpb_mgr->ps_dpb_ht_head;
 if(ps_next_dpb->u1_lt_idx == u4_lt_idx)
 {
            ps_unmark_node = ps_next_dpb;
 }
 else
 {
 for(i = 1; i < ps_dpb_mgr->u1_num_lt_ref_bufs; i++)
 {
 if(ps_next_dpb->ps_prev_long->u1_lt_idx == u4_lt_idx)
 break;
                ps_next_dpb = ps_next_dpb->ps_prev_long;
 }
 if(i == ps_dpb_mgr->u1_num_lt_ref_bufs)
 *pi4_status = 1;
 else
                ps_unmark_node = ps_next_dpb->ps_prev_long;
 }

 if(*pi4_status == 0)
 {
 if(u1_fld_pic_flag)
 {
 if(ps_lt_node_to_insert != ps_unmark_node)
 {
                    UWORD8 u1_deleted = 0;
 /* for the ps_unmark_node mark the corresponding field */
 /* field as unused for reference                       */

 if(ps_unmark_node->s_top_field.u1_long_term_frame_idx
 == u4_lt_idx)
 {
                        ps_unmark_node->s_top_field.u1_reference_info =
                                        UNUSED_FOR_REF;
                        ps_unmark_node->s_top_field.u1_long_term_frame_idx =
                        MAX_REF_BUFS + 1;
                        u1_deleted = 1;
 }
 if(ps_unmark_node->s_bot_field.u1_long_term_frame_idx
 == u4_lt_idx)
 {
                        ps_unmark_node->s_bot_field.u1_reference_info =
                                        UNUSED_FOR_REF;
                        ps_unmark_node->s_bot_field.u1_long_term_frame_idx =
                        MAX_REF_BUFS + 1;
                        u1_deleted = 1;
 }

 if(!u1_deleted)
 {

                        UWORD32 i4_error_code;
                        i4_error_code = ERROR_DBP_MANAGER_T;

 return i4_error_code;
 }
 }

                ps_unmark_node->u1_used_as_ref =
                                ps_unmark_node->s_top_field.u1_reference_info
 | ps_unmark_node->s_bot_field.u1_reference_info;
 }
 else
                ps_unmark_node->u1_used_as_ref = UNUSED_FOR_REF;

 if(UNUSED_FOR_REF == ps_unmark_node->u1_used_as_ref)
 {
 if(ps_unmark_node == ps_dpb_mgr->ps_dpb_ht_head)
                    ps_dpb_mgr->ps_dpb_ht_head = ps_next_dpb->ps_prev_long;

                ps_unmark_node->u1_lt_idx = MAX_REF_BUFS + 1;
                ps_unmark_node->s_top_field.u1_reference_info =
                UNUSED_FOR_REF;
                ps_unmark_node->s_bot_field.u1_reference_info =
                UNUSED_FOR_REF;
                ih264d_free_ref_pic_mv_bufs(ps_dpb_mgr->pv_codec_handle,
                                            ps_unmark_node->u1_buf_id);
                ps_next_dpb->ps_prev_long = ps_unmark_node->ps_prev_long; //update link
                ps_unmark_node->ps_prev_long = NULL;
                ps_dpb_mgr->u1_num_lt_ref_bufs--; //decrement LT buf count
 }
 }
 }
 return OK;
}
