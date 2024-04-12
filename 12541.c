midi_synth_set_instr(int dev, int channel, int instr_no)
{
	int             orig_dev = synth_devs[dev]->midi_dev;

	if (instr_no < 0 || instr_no > 127)
		instr_no = 0;
	if (channel < 0 || channel > 15)
		return 0;

	leave_sysex(dev);

	if (!prefix_cmd(orig_dev, 0xc0 | (channel & 0x0f)))
		return 0;
	midi_outc(orig_dev, 0xc0 | (channel & 0x0f));	/*
							 * Program change
							 */
	midi_outc(orig_dev, instr_no);

	return 0;
}
