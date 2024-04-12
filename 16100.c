static void print_serial(sc_card_t *in_card)
{
	int r;
	sc_serial_number_t serial;

	r = sc_lock(card);
	if (r == SC_SUCCESS)
		r = sc_card_ctl(in_card, SC_CARDCTL_GET_SERIALNR, &serial);
	sc_unlock(card);
	if (r)
		fprintf(stderr, "sc_card_ctl(*, SC_CARDCTL_GET_SERIALNR, *) failed\n");
	else
		util_hex_dump_asc(stdout, serial.value, serial.len, -1);
}
