static int card_reset(const char *reset_type)
{
	int cold_reset;
	int r;

	if (reset_type && strcmp(reset_type, "cold") &&
	    strcmp(reset_type, "warm")) {
		fprintf(stderr, "Invalid reset type: %s\n", reset_type);
		return 2;
	}

	cold_reset = !reset_type || strcmp(reset_type, "cold") == 0;

	r = sc_lock(card);
	if (r == SC_SUCCESS)
		r = sc_reset(card, cold_reset);
	sc_unlock(card);
	if (r) {
		fprintf(stderr, "sc_reset(%s) failed: %d\n",
			cold_reset ? "cold" : "warm", r);
		return 1;
	}

	return 0;
}
