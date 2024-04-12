static int in_set_format(struct audio_stream *stream, audio_format_t format)
{
    UNUSED(stream);
    UNUSED(format);

    FNLOG();
 if (format == AUDIO_FORMAT_PCM_16_BIT)
 return 0;
 else
 return -1;
}
