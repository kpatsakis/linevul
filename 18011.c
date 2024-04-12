static int alloc_voice(int dev, int chn, int note)
{
	unsigned short  key;
	int voice;

	key = (chn << 8) | (note + 1);

	voice = synth_devs[dev]->alloc_voice(dev, chn, note,
					     &synth_devs[dev]->alloc);
	synth_devs[dev]->alloc.map[voice] = key;
	synth_devs[dev]->alloc.alloc_times[voice] =
			synth_devs[dev]->alloc.timestamp++;
	return voice;
}
