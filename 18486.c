IHEVCD_ERROR_T ihevcd_parse_coding_quadtree(codec_t *ps_codec,
                                            WORD32 x0,
                                            WORD32 y0,
                                            WORD32 log2_cb_size,
                                            WORD32 ct_depth)
{
    IHEVCD_ERROR_T ret = (IHEVCD_ERROR_T)IHEVCD_SUCCESS;
 sps_t *ps_sps;
 pps_t *ps_pps;
    WORD32 split_cu_flag;
    WORD32 x1, y1;
    WORD32 cu_pos_x;
    WORD32 cu_pos_y;
 bitstrm_t *ps_bitstrm = &ps_codec->s_parse.s_bitstrm;
 cab_ctxt_t *ps_cabac = &ps_codec->s_parse.s_cabac;
    WORD32 cb_size = 1 << log2_cb_size;
    ps_sps = ps_codec->s_parse.ps_sps;
    ps_pps = ps_codec->s_parse.ps_pps;

 /* Compute CU position with respect to current CTB in (8x8) units */
    cu_pos_x = (x0 - (ps_codec->s_parse.i4_ctb_x << ps_sps->i1_log2_ctb_size)) >> 3;
    cu_pos_y = (y0 - (ps_codec->s_parse.i4_ctb_y << ps_sps->i1_log2_ctb_size)) >> 3;

    ps_codec->s_parse.s_cu.i4_pos_x = cu_pos_x;
    ps_codec->s_parse.s_cu.i4_pos_y = cu_pos_y;

    ps_codec->s_parse.s_cu.i4_log2_cb_size = log2_cb_size;

    ps_codec->s_parse.i4_ct_depth = ct_depth;
 {
        UWORD32 *pu4_ct_depth_top = ps_codec->s_parse.pu4_ct_depth_top;
        UWORD32 u4_ct_depth_left = ps_codec->s_parse.u4_ct_depth_left;
        UWORD32 u4_ct_depth_top = 0;
        UWORD32 u4_mask;
        UWORD32 u4_top_mask, u4_left_mask;
        WORD32  ctxt_idx;
        UWORD32 u4_min_cu_x = x0 / 8;
        UWORD32 u4_min_cu_y = y0 / 8;

        pu4_ct_depth_top += (u4_min_cu_x / 16);




 if(((x0 + (1 << log2_cb_size)) <= ps_sps->i2_pic_width_in_luma_samples) &&
 ((y0 + (1 << log2_cb_size)) <= ps_sps->i2_pic_height_in_luma_samples) &&
 (log2_cb_size > ps_sps->i1_log2_min_coding_block_size))
 {

            ctxt_idx = IHEVC_CAB_SPLIT_CU_FLAG;
 /* Split cu context increment is decided based on left and top Coding tree
             * depth which is stored at frame level
             */
 /* Check if the CTB is in first row in the current slice or tile */
 if((0 != cu_pos_y) ||
 ((0 != ps_codec->s_parse.i4_ctb_slice_y) &&
 (0 != ps_codec->s_parse.i4_ctb_tile_y)))
 {
                u4_ct_depth_top = *pu4_ct_depth_top;
                u4_ct_depth_top >>= ((u4_min_cu_x % 16) * 2);
                u4_ct_depth_top &= 3;

 if((WORD32)u4_ct_depth_top > ct_depth)
                    ctxt_idx++;
 }

 /* Check if the CTB is in first column in the current slice or tile */
 /*****************************************************************/
 /* If cu_pos_x is non-zero then left is available                */
 /* If cu_pos_x is zero then ensure both the following are true   */
 /*    Current CTB is not the first CTB in a tile row             */
 /*    Current CTB is not the first CTB in a slice                */
 /*****************************************************************/
 if((0 != cu_pos_x) ||
 (((0 != ps_codec->s_parse.i4_ctb_slice_x) || (0 != ps_codec->s_parse.i4_ctb_slice_y)) &&
 (0 != ps_codec->s_parse.i4_ctb_tile_x)))
 {
                u4_ct_depth_left >>= ((u4_min_cu_y % 16) * 2);
                u4_ct_depth_left &= 3;
 if((WORD32)u4_ct_depth_left > ct_depth)
                    ctxt_idx++;
 }
            TRACE_CABAC_CTXT("split_cu_flag", ps_cabac->u4_range, ctxt_idx);
            split_cu_flag = ihevcd_cabac_decode_bin(ps_cabac, ps_bitstrm, ctxt_idx);
            AEV_TRACE("split_cu_flag", split_cu_flag, ps_cabac->u4_range);
 }
 else
 {
 if(log2_cb_size > ps_sps->i1_log2_min_coding_block_size)
                split_cu_flag = 1;
 else
                split_cu_flag = 0;
 }

 if(0 == split_cu_flag)
 {
 /* Update top ct_depth */
            u4_ct_depth_top = *pu4_ct_depth_top;
 /* Since Max cb_size is 64, maximum of 8 bits will be set or reset */
 /* Also since Coding block will be within 64x64 grid, only 8bits within a WORD32
             * need to be updated. These 8 bits will not cross 8 bit boundaries
             */
            u4_mask = DUP_LSB_11(cb_size / 8);

            u4_top_mask = u4_mask << ((u4_min_cu_x % 16) * 2);
            u4_ct_depth_top &= ~u4_top_mask;

 if(ct_depth)
 {
                u4_top_mask = gau4_ct_depth_mask[ct_depth] & u4_mask;

                u4_top_mask = u4_top_mask << ((u4_min_cu_x % 16) * 2);
                u4_ct_depth_top |= u4_top_mask;
 }

 *pu4_ct_depth_top = u4_ct_depth_top;

 /* Update left ct_depth */
            u4_ct_depth_left = ps_codec->s_parse.u4_ct_depth_left;

            u4_left_mask = u4_mask << ((u4_min_cu_y % 16) * 2);

            u4_ct_depth_left &= ~u4_left_mask;
 if(ct_depth)
 {
                u4_left_mask = gau4_ct_depth_mask[ct_depth] & u4_mask;

                u4_left_mask = u4_left_mask << ((u4_min_cu_y % 16) * 2);
                u4_ct_depth_left |= u4_left_mask;
 }

            ps_codec->s_parse.u4_ct_depth_left = u4_ct_depth_left;
 }
 }
 if((ps_pps->i1_cu_qp_delta_enabled_flag) &&
 (log2_cb_size >= ps_pps->i1_log2_min_cu_qp_delta_size))
 {
        ps_codec->s_parse.i4_is_cu_qp_delta_coded = 0;
        ps_codec->s_parse.i4_cu_qp_delta = 0;
 }
 if(split_cu_flag)
 {
        x1 = x0 + ((1 << log2_cb_size) >> 1);
        y1 = y0 + ((1 << log2_cb_size) >> 1);

        ret = ihevcd_parse_coding_quadtree(ps_codec, x0, y0, log2_cb_size - 1, ct_depth + 1);
        RETURN_IF((IHEVCD_ERROR_T)IHEVCD_SUCCESS != ret, ret);

 /* At frame boundaries coding quadtree nodes are sent only if they fall within the frame */
 if(x1 < ps_sps->i2_pic_width_in_luma_samples)
 {
            ret = ihevcd_parse_coding_quadtree(ps_codec, x1, y0, log2_cb_size - 1, ct_depth + 1);
            RETURN_IF((IHEVCD_ERROR_T)IHEVCD_SUCCESS != ret, ret);
 }

 if(y1 < ps_sps->i2_pic_height_in_luma_samples)
 {
            ret = ihevcd_parse_coding_quadtree(ps_codec, x0, y1, log2_cb_size - 1, ct_depth + 1);
            RETURN_IF((IHEVCD_ERROR_T)IHEVCD_SUCCESS != ret, ret);
 }

 if((x1 < ps_sps->i2_pic_width_in_luma_samples) &&
 (y1 < ps_sps->i2_pic_height_in_luma_samples))
 {
            ret = ihevcd_parse_coding_quadtree(ps_codec, x1, y1, log2_cb_size - 1, ct_depth + 1);
            RETURN_IF((IHEVCD_ERROR_T)IHEVCD_SUCCESS != ret, ret);
 }
 }
 else
 {
 /* Set current group QP if current CU is aligned with the group */
 {
            WORD32 cu_pos_x = ps_codec->s_parse.s_cu.i4_pos_x << 3;
            WORD32 cu_pos_y = ps_codec->s_parse.s_cu.i4_pos_y << 3;

            WORD32 qpg_x = (cu_pos_x - (cu_pos_x & ((1 << ps_pps->i1_log2_min_cu_qp_delta_size) - 1)));
            WORD32 qpg_y = (cu_pos_y - (cu_pos_y & ((1 << ps_pps->i1_log2_min_cu_qp_delta_size) - 1)));

 if((cu_pos_x == qpg_x) &&
 (cu_pos_y == qpg_y))
 {
                ps_codec->s_parse.u4_qpg = ps_codec->s_parse.u4_qp;

                ps_codec->s_parse.s_cu.i4_cu_qp_delta = 0;

 }
 }

        ret = ihevcd_parse_coding_unit(ps_codec, x0, y0, log2_cb_size);
        RETURN_IF((IHEVCD_ERROR_T)IHEVCD_SUCCESS != ret, ret);

 if(ps_pps->i1_cu_qp_delta_enabled_flag)
 {
            WORD32 qp_pred, qp_left, qp_top;
            WORD32 cu_pos_x;
            WORD32 cu_pos_y;
            WORD32 qpg_x;
            WORD32 qpg_y;
            WORD32 i, j;
            WORD32 qp;
            WORD32 cur_cu_offset;
 tu_t *ps_tu = ps_codec->s_parse.ps_tu;
            WORD32 cb_size = 1 << ps_codec->s_parse.s_cu.i4_log2_cb_size;

            cu_pos_x = ps_codec->s_parse.s_cu.i4_pos_x << 3;
            cu_pos_y = ps_codec->s_parse.s_cu.i4_pos_y << 3;

            qpg_x = (cu_pos_x - (cu_pos_x & ((1 << ps_pps->i1_log2_min_cu_qp_delta_size) - 1))) >> 3;
            qpg_y = (cu_pos_y - (cu_pos_y & ((1 << ps_pps->i1_log2_min_cu_qp_delta_size) - 1))) >> 3;

 /*previous coded Qp*/
            qp_left = ps_codec->s_parse.u4_qpg;
            qp_top = ps_codec->s_parse.u4_qpg;

 if(qpg_x > 0)
 {
                qp_left = ps_codec->s_parse.ai1_8x8_cu_qp[qpg_x - 1 + (qpg_y * 8)];
 }
 if(qpg_y > 0)
 {
                qp_top = ps_codec->s_parse.ai1_8x8_cu_qp[qpg_x + ((qpg_y - 1) * 8)];
 }

            qp_pred = (qp_left + qp_top + 1) >> 1;
 /* Since qp_pred + ps_codec->s_parse.s_cu.i4_cu_qp_delta can be negative,
            52 is added before taking modulo 52 */
            qp = (qp_pred + ps_codec->s_parse.s_cu.i4_cu_qp_delta + 52) % 52;

            cur_cu_offset = (cu_pos_x >> 3) + cu_pos_y;
 for(i = 0; i < (cb_size >> 3); i++)
 {
 for(j = 0; j < (cb_size >> 3); j++)
 {
                    ps_codec->s_parse.ai1_8x8_cu_qp[cur_cu_offset + (i * 8) + j] = qp;
 }
 }

            ps_codec->s_parse.u4_qp = qp;
            ps_codec->s_parse.s_cu.i4_qp = qp;


 /* When change in QP is signaled, update the QP in TUs that are already parsed in the CU */
 {
 tu_t *ps_tu_tmp;
                ps_tu_tmp = ps_tu - ps_codec->s_parse.s_cu.i4_tu_cnt;
                ps_tu->b7_qp = ps_codec->s_parse.u4_qp;
 while(ps_tu_tmp != ps_tu)
 {
                    ps_tu_tmp->b7_qp = ps_codec->s_parse.u4_qp;

                    ps_tu_tmp++;
 }
 }
 if(ps_codec->s_parse.s_cu.i4_cu_qp_delta)
 {
                WORD32 ctb_indx;
                ctb_indx = ps_codec->s_parse.i4_ctb_x + ps_sps->i2_pic_wd_in_ctb * ps_codec->s_parse.i4_ctb_y;
                ps_codec->s_parse.s_bs_ctxt.pu1_pic_qp_const_in_ctb[ctb_indx >> 3] &= (~(1 << (ctb_indx & 7)));
 }

 }

 }




 return ret;
}
