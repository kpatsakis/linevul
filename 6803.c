static int decode_studio_vol_header(Mpeg4DecContext *ctx, GetBitContext *gb)
{
    MpegEncContext *s = &ctx->m;
    int width, height;
    int bits_per_raw_sample;

            skip_bits(gb, 4); /* video_object_layer_verid */
            ctx->shape = get_bits(gb, 2); /* video_object_layer_shape */
            skip_bits(gb, 4); /* video_object_layer_shape_extension */
            skip_bits1(gb); /* progressive_sequence */
            if (ctx->shape != BIN_ONLY_SHAPE) {
                ctx->rgb = get_bits1(gb); /* rgb_components */
                s->chroma_format = get_bits(gb, 2); /* chroma_format */
                if (!s->chroma_format) {
                    av_log(s->avctx, AV_LOG_ERROR, "illegal chroma format\n");
                    return AVERROR_INVALIDDATA;
                }

                bits_per_raw_sample = get_bits(gb, 4); /* bit_depth */
                if (bits_per_raw_sample == 10) {
                    if (ctx->rgb) {
                        s->avctx->pix_fmt = AV_PIX_FMT_GBRP10;
                    }
                    else {
                        s->avctx->pix_fmt = s->chroma_format == CHROMA_422 ? AV_PIX_FMT_YUV422P10 : AV_PIX_FMT_YUV444P10;
                    }
                }
                else {
                    avpriv_request_sample(s->avctx, "MPEG-4 Studio profile bit-depth %u", bits_per_raw_sample);
                    return AVERROR_PATCHWELCOME;
                }
                s->avctx->bits_per_raw_sample = bits_per_raw_sample;
            }
            if (ctx->shape == RECT_SHAPE) {
                check_marker(s->avctx, gb, "before video_object_layer_width");
                width = get_bits(gb, 14); /* video_object_layer_width */
                check_marker(s->avctx, gb, "before video_object_layer_height");
                height = get_bits(gb, 14); /* video_object_layer_height */
                check_marker(s->avctx, gb, "after video_object_layer_height");

                /* Do the same check as non-studio profile */
                if (width && height) {
                    if (s->width && s->height &&
                        (s->width != width || s->height != height))
                        s->context_reinit = 1;
                    s->width  = width;
                    s->height = height;
                }
            }
            s->aspect_ratio_info = get_bits(gb, 4);
            if (s->aspect_ratio_info == FF_ASPECT_EXTENDED) {
                s->avctx->sample_aspect_ratio.num = get_bits(gb, 8);  // par_width
                s->avctx->sample_aspect_ratio.den = get_bits(gb, 8);  // par_height
            } else {
                s->avctx->sample_aspect_ratio = ff_h263_pixel_aspect[s->aspect_ratio_info];
            }
            skip_bits(gb, 4); /* frame_rate_code */
            skip_bits(gb, 15); /* first_half_bit_rate */
            check_marker(s->avctx, gb, "after first_half_bit_rate");
            skip_bits(gb, 15); /* latter_half_bit_rate */
            check_marker(s->avctx, gb, "after latter_half_bit_rate");
            skip_bits(gb, 15); /* first_half_vbv_buffer_size */
            check_marker(s->avctx, gb, "after first_half_vbv_buffer_size");
            skip_bits(gb, 3); /* latter_half_vbv_buffer_size */
            skip_bits(gb, 11); /* first_half_vbv_buffer_size */
            check_marker(s->avctx, gb, "after first_half_vbv_buffer_size");
            skip_bits(gb, 15); /* latter_half_vbv_occupancy */
            check_marker(s->avctx, gb, "after latter_half_vbv_occupancy");
            s->low_delay = get_bits1(gb);
            s->mpeg_quant = get_bits1(gb); /* mpeg2_stream */

            next_start_code_studio(gb);
            extension_and_user_data(s, gb, 2);

    return 0;
}
