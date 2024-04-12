static size_t in_get_buffer_size(const struct audio_stream *stream)
{
 struct stream_in *in = (struct stream_in *)stream;

 return get_input_buffer_size(in->requested_rate,
                                 in_get_format(stream),
                                 audio_channel_count_from_in_mask(in->main_channels),
                                 in->usecase_type,
                                 in->devices);
}
