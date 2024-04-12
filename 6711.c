static uint32_t out_get_channels(const struct audio_stream *stream)
{
 struct stream_out *out = (struct stream_out *)stream;

 return out->channel_mask;
}
