xscale1_pmnc_counter_has_overflowed(unsigned long pmnc,
					enum xscale_counters counter)
{
	int ret = 0;

	switch (counter) {
	case XSCALE_CYCLE_COUNTER:
		ret = pmnc & XSCALE1_CCOUNT_OVERFLOW;
		break;
	case XSCALE_COUNTER0:
		ret = pmnc & XSCALE1_COUNT0_OVERFLOW;
		break;
	case XSCALE_COUNTER1:
		ret = pmnc & XSCALE1_COUNT1_OVERFLOW;
		break;
	default:
		WARN_ONCE(1, "invalid counter number (%d)\n", counter);
	}

	return ret;
}
