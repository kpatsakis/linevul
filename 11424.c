static size_t out_get_buffer_size(const struct audio_stream *stream)
{
 struct a2dp_stream_out *out = (struct a2dp_stream_out *)stream;

    DEBUG("buffer_size : %zu", out->common.buffer_sz);

 return out->common.buffer_sz;
}
