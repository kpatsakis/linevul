static void vc1_put_blocks_clamped(VC1Context *v, int put_signed)
{
    MpegEncContext *s = &v->s;
    uint8_t *dest;
    int block_count = CONFIG_GRAY && (s->avctx->flags & AV_CODEC_FLAG_GRAY) ? 4 : 6;
    int fieldtx = 0;
    int i;

    /* The put pixels loop is one MB row and one MB column behind the decoding
     * loop because we can only put pixels when overlap filtering is done. For
     * interlaced frame pictures, however, the put pixels loop is only one
     * column behind the decoding loop as interlaced frame pictures only need
     * horizontal overlap filtering. */
    if (!s->first_slice_line && v->fcm != ILACE_FRAME) {
        if (s->mb_x) {
            for (i = 0; i < block_count; i++) {
                if (i > 3 ? v->mb_type[0][s->block_index[i] - s->block_wrap[i] - 1] :
                            v->mb_type[0][s->block_index[i] - 2 * s->block_wrap[i] - 2]) {
                    dest = s->dest[0] + ((i & 2) - 4) * 4 * s->linesize + ((i & 1) - 2) * 8;
                    if (put_signed)
                        s->idsp.put_signed_pixels_clamped(v->block[v->topleft_blk_idx][block_map[i]],
                                                          i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize - 8 : dest,
                                                          i > 3 ? s->uvlinesize : s->linesize);
                    else
                        s->idsp.put_pixels_clamped(v->block[v->topleft_blk_idx][block_map[i]],
                                                   i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize - 8 : dest,
                                                   i > 3 ? s->uvlinesize : s->linesize);
                }
            }
        }
        if (s->mb_x == v->end_mb_x - 1) {
            for (i = 0; i < block_count; i++) {
                if (i > 3 ? v->mb_type[0][s->block_index[i] - s->block_wrap[i]] :
                            v->mb_type[0][s->block_index[i] - 2 * s->block_wrap[i]]) {
                    dest = s->dest[0] + ((i & 2) - 4) * 4 * s->linesize + (i & 1) * 8;
                    if (put_signed)
                        s->idsp.put_signed_pixels_clamped(v->block[v->top_blk_idx][block_map[i]],
                                                          i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize : dest,
                                                          i > 3 ? s->uvlinesize : s->linesize);
                    else
                        s->idsp.put_pixels_clamped(v->block[v->top_blk_idx][block_map[i]],
                                                   i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize : dest,
                                                   i > 3 ? s->uvlinesize : s->linesize);
                }
            }
        }
    }
    if (s->mb_y == s->end_mb_y - 1 || v->fcm == ILACE_FRAME) {
        if (s->mb_x) {
            if (v->fcm == ILACE_FRAME)
                fieldtx = v->fieldtx_plane[s->mb_y * s->mb_stride + s->mb_x - 1];
            for (i = 0; i < block_count; i++) {
                if (i > 3 ? v->mb_type[0][s->block_index[i] - 1] :
                            v->mb_type[0][s->block_index[i] - 2]) {
                    if (fieldtx)
                        dest = s->dest[0] + ((i & 2) >> 1) * s->linesize + ((i & 1) - 2) * 8;
                    else
                        dest = s->dest[0] + (i & 2) * 4 * s->linesize + ((i & 1) - 2) * 8;
                    if (put_signed)
                        s->idsp.put_signed_pixels_clamped(v->block[v->left_blk_idx][block_map[i]],
                                                          i > 3 ? s->dest[i - 3] - 8 : dest,
                                                          i > 3 ? s->uvlinesize : s->linesize << fieldtx);
                    else
                        s->idsp.put_pixels_clamped(v->block[v->left_blk_idx][block_map[i]],
                                                   i > 3 ? s->dest[i - 3] - 8 : dest,
                                                   i > 3 ? s->uvlinesize : s->linesize << fieldtx);
                }
            }
        }
        if (s->mb_x == v->end_mb_x - 1) {
            if (v->fcm == ILACE_FRAME)
                fieldtx = v->fieldtx_plane[s->mb_y * s->mb_stride + s->mb_x];
            for (i = 0; i < block_count; i++) {
                if (v->mb_type[0][s->block_index[i]]) {
                    if (fieldtx)
                        dest = s->dest[0] + ((i & 2) >> 1) * s->linesize + (i & 1) * 8;
                    else
                        dest = s->dest[0] + (i & 2) * 4 * s->linesize + (i & 1) * 8;
                    if (put_signed)
                        s->idsp.put_signed_pixels_clamped(v->block[v->cur_blk_idx][block_map[i]],
                                                          i > 3 ? s->dest[i - 3] : dest,
                                                          i > 3 ? s->uvlinesize : s->linesize << fieldtx);
                    else
                        s->idsp.put_pixels_clamped(v->block[v->cur_blk_idx][block_map[i]],
                                                   i > 3 ? s->dest[i - 3] : dest,
                                                   i > 3 ? s->uvlinesize : s->linesize << fieldtx);
                }
            }
        }
    }
}
