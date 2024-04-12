static size_t out_get_buffer_size(const struct audio_stream *stream)
{
 struct stream_out *out = (struct stream_out *)stream;

 return out->config.period_size *
               audio_stream_out_frame_size((const struct audio_stream_out *)stream);
}
