int sequencer_open(int dev, struct file *file)
{
	int retval, mode, i;
	int level, tmp;

	if (!sequencer_ok)
		sequencer_init();

	level = ((dev & 0x0f) == SND_DEV_SEQ2) ? 2 : 1;

	dev = dev >> 4;
	mode = translate_mode(file);

	DEB(printk("sequencer_open(dev=%d)\n", dev));

	if (!sequencer_ok)
	{
/*		printk("Sound card: sequencer not initialized\n");*/
		return -ENXIO;
	}
	if (dev)		/* Patch manager device (obsolete) */
		return -ENXIO;

	if(synth_devs[dev] == NULL)
		request_module("synth0");

	if (mode == OPEN_READ)
	{
		if (!num_midis)
		{
			/*printk("Sequencer: No MIDI devices. Input not possible\n");*/
			sequencer_busy = 0;
			return -ENXIO;
		}
	}
	if (sequencer_busy)
	{
		return -EBUSY;
	}
	sequencer_busy = 1;
	obsolete_api_used = 0;

	max_mididev = num_midis;
	max_synthdev = num_synths;
	pre_event_timeout = MAX_SCHEDULE_TIMEOUT;
	seq_mode = SEQ_1;

	if (pending_timer != -1)
	{
		tmr_no = pending_timer;
		pending_timer = -1;
	}
	if (tmr_no == -1)	/* Not selected yet */
	{
		int i, best;

		best = -1;
		for (i = 0; i < num_sound_timers; i++)
			if (sound_timer_devs[i] && sound_timer_devs[i]->priority > best)
			{
				tmr_no = i;
				best = sound_timer_devs[i]->priority;
			}
		if (tmr_no == -1)	/* Should not be */
			tmr_no = 0;
	}
	tmr = sound_timer_devs[tmr_no];

	if (level == 2)
	{
		if (tmr == NULL)
		{
			/*printk("sequencer: No timer for level 2\n");*/
			sequencer_busy = 0;
			return -ENXIO;
		}
		setup_mode2();
	}
	if (!max_synthdev && !max_mididev)
	{
		sequencer_busy=0;
		return -ENXIO;
	}

	synth_open_mask = 0;

	for (i = 0; i < max_mididev; i++)
	{
		midi_opened[i] = 0;
		midi_written[i] = 0;
	}

	for (i = 0; i < max_synthdev; i++)
	{
		if (synth_devs[i]==NULL)
			continue;

		if (!try_module_get(synth_devs[i]->owner))
			continue;

		if ((tmp = synth_devs[i]->open(i, mode)) < 0)
		{
			printk(KERN_WARNING "Sequencer: Warning! Cannot open synth device #%d (%d)\n", i, tmp);
			if (synth_devs[i]->midi_dev)
				printk(KERN_WARNING "(Maps to MIDI dev #%d)\n", synth_devs[i]->midi_dev);
		}
		else
		{
			synth_open_mask |= (1 << i);
			if (synth_devs[i]->midi_dev)
				midi_opened[synth_devs[i]->midi_dev] = 1;
		}
	}

	seq_time = jiffies;

	prev_input_time = 0;
	prev_event_time = 0;

	if (seq_mode == SEQ_1 && (mode == OPEN_READ || mode == OPEN_READWRITE))
	{
		/*
		 * Initialize midi input devices
		 */

		for (i = 0; i < max_mididev; i++)
			if (!midi_opened[i] && midi_devs[i])
			{
				if (!try_module_get(midi_devs[i]->owner))
					continue;
	
				if ((retval = midi_devs[i]->open(i, mode,
					sequencer_midi_input, sequencer_midi_output)) >= 0)
				{
					midi_opened[i] = 1;
				}
			}
	}

	if (seq_mode == SEQ_2) {
		if (try_module_get(tmr->owner))
			tmr->open(tmr_no, seq_mode);
	}

 	init_waitqueue_head(&seq_sleeper);
 	init_waitqueue_head(&midi_sleeper);
	output_threshold = SEQ_MAX_QUEUE / 2;

	return 0;
}
