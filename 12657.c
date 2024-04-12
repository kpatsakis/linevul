static int snd_usb_mixer_controls(struct usb_mixer_interface *mixer)
{
	struct mixer_build state;
	int err;
	const struct usbmix_ctl_map *map;
	void *p;

	memset(&state, 0, sizeof(state));
	state.chip = mixer->chip;
	state.mixer = mixer;
	state.buffer = mixer->hostif->extra;
	state.buflen = mixer->hostif->extralen;

	/* check the mapping table */
	for (map = usbmix_ctl_maps; map->id; map++) {
		if (map->id == state.chip->usb_id) {
			state.map = map->map;
			state.selector_map = map->selector_map;
			mixer->ignore_ctl_error = map->ignore_ctl_error;
			break;
		}
	}

	p = NULL;
	while ((p = snd_usb_find_csint_desc(mixer->hostif->extra,
					    mixer->hostif->extralen,
					    p, UAC_OUTPUT_TERMINAL)) != NULL) {
		if (mixer->protocol == UAC_VERSION_1) {
			struct uac1_output_terminal_descriptor *desc = p;

			if (desc->bLength < sizeof(*desc))
				continue; /* invalid descriptor? */
			/* mark terminal ID as visited */
			set_bit(desc->bTerminalID, state.unitbitmap);
			state.oterm.id = desc->bTerminalID;
			state.oterm.type = le16_to_cpu(desc->wTerminalType);
			state.oterm.name = desc->iTerminal;
			err = parse_audio_unit(&state, desc->bSourceID);
			if (err < 0 && err != -EINVAL)
				return err;
		} else { /* UAC_VERSION_2 */
			struct uac2_output_terminal_descriptor *desc = p;

			if (desc->bLength < sizeof(*desc))
				continue; /* invalid descriptor? */
			/* mark terminal ID as visited */
			set_bit(desc->bTerminalID, state.unitbitmap);
			state.oterm.id = desc->bTerminalID;
			state.oterm.type = le16_to_cpu(desc->wTerminalType);
			state.oterm.name = desc->iTerminal;
			err = parse_audio_unit(&state, desc->bSourceID);
			if (err < 0 && err != -EINVAL)
				return err;

			/*
			 * For UAC2, use the same approach to also add the
			 * clock selectors
			 */
			err = parse_audio_unit(&state, desc->bCSourceID);
			if (err < 0 && err != -EINVAL)
				return err;
		}
	}

	return 0;
}
