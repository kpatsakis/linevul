static void set_mv_strides(ERContext *s, ptrdiff_t *mv_step, ptrdiff_t *stride)
{
    if (s->avctx->codec_id == AV_CODEC_ID_H264) {
        av_assert0(s->quarter_sample);
        *mv_step = 4;
        *stride  = s->mb_width * 4;
    } else {
        *mv_step = 2;
        *stride  = s->b8_stride;
    }
}
