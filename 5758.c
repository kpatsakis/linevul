void SoundChannel::callback(int event, void* user, void *info)
{
 SoundChannel* channel = static_cast<SoundChannel*>((void *)((unsigned long)user & ~1));

    channel->process(event, info, (unsigned long)user & 1);
}
