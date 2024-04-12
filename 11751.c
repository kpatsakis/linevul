static void snd_msndmidi_input_trigger(struct snd_rawmidi_substream *substream,
					int up)
{
	unsigned long flags;
	struct snd_msndmidi *mpu;

	snd_printdd("snd_msndmidi_input_trigger(, %i)\n", up);

	mpu = substream->rmidi->private_data;
	spin_lock_irqsave(&mpu->input_lock, flags);
	if (up) {
		if (!test_and_set_bit(MSNDMIDI_MODE_BIT_INPUT_TRIGGER,
				      &mpu->mode))
			snd_msndmidi_input_drop(mpu);
	} else {
		clear_bit(MSNDMIDI_MODE_BIT_INPUT_TRIGGER, &mpu->mode);
	}
	spin_unlock_irqrestore(&mpu->input_lock, flags);
	if (up)
		snd_msndmidi_input_read(mpu);
}
