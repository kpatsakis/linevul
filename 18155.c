static int calc_audiotime(struct a2dp_config cfg, int bytes)
{
 int chan_count = popcount(cfg.channel_flags);

    ASSERTC(cfg.format == AUDIO_FORMAT_PCM_16_BIT,
 "unsupported sample sz", cfg.format);

 return bytes*(1000000/(chan_count*2))/cfg.rate;
}
