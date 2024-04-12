static void setup_mode2(void)
{
	int dev;

	max_synthdev = num_synths;

	for (dev = 0; dev < num_midis; dev++)
	{
		if (midi_devs[dev] && midi_devs[dev]->converter != NULL)
		{
			synth_devs[max_synthdev++] = midi_devs[dev]->converter;
		}
	}

	for (dev = 0; dev < max_synthdev; dev++)
	{
		int chn;

		synth_devs[dev]->sysex_ptr = 0;
		synth_devs[dev]->emulation = 0;

		for (chn = 0; chn < 16; chn++)
		{
			synth_devs[dev]->chn_info[chn].pgm_num = 0;
			reset_controllers(dev,
				synth_devs[dev]->chn_info[chn].controllers,0);
			synth_devs[dev]->chn_info[chn].bender_value = (1 << 7);	/* Neutral */
			synth_devs[dev]->chn_info[chn].bender_range = 200;
		}
	}
	max_mididev = 0;
	seq_mode = SEQ_2;
}
