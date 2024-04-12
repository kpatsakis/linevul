static int ev67_check_constraints(struct perf_event **event,
				unsigned long *evtype, int n_ev)
{
	int idx0;
	unsigned long config;

	idx0 = ev67_mapping[evtype[0]-1].idx;
	config = ev67_mapping[evtype[0]-1].config;
	if (n_ev == 1)
		goto success;

	BUG_ON(n_ev != 2);

	if (evtype[0] == EV67_MBOXREPLAY || evtype[1] == EV67_MBOXREPLAY) {
		/* MBOX replay traps must be on PMC 1 */
		idx0 = (evtype[0] == EV67_MBOXREPLAY) ? 1 : 0;
		/* Only cycles can accompany MBOX replay traps */
		if (evtype[idx0] == EV67_CYCLES) {
			config = EV67_PCTR_CYCLES_MBOX;
			goto success;
		}
	}

	if (evtype[0] == EV67_BCACHEMISS || evtype[1] == EV67_BCACHEMISS) {
		/* Bcache misses must be on PMC 1 */
		idx0 = (evtype[0] == EV67_BCACHEMISS) ? 1 : 0;
		/* Only instructions can accompany Bcache misses */
		if (evtype[idx0] == EV67_INSTRUCTIONS) {
			config = EV67_PCTR_INSTR_BCACHEMISS;
			goto success;
		}
	}

	if (evtype[0] == EV67_INSTRUCTIONS || evtype[1] == EV67_INSTRUCTIONS) {
		/* Instructions must be on PMC 0 */
		idx0 = (evtype[0] == EV67_INSTRUCTIONS) ? 0 : 1;
		/* By this point only cycles can accompany instructions */
		if (evtype[idx0^1] == EV67_CYCLES) {
			config = EV67_PCTR_INSTR_CYCLES;
			goto success;
		}
	}

	/* Otherwise, darn it, there is a conflict.  */
	return -1;

success:
	event[0]->hw.idx = idx0;
	event[0]->hw.config_base = config;
	if (n_ev == 2) {
		event[1]->hw.idx = idx0 ^ 1;
		event[1]->hw.config_base = config;
	}
	return 0;
}
