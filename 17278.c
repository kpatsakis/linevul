static void p4_pmu_disable_pebs(void)
{
	/*
	 * FIXME
	 *
	 * It's still allowed that two threads setup same cache
	 * events so we can't simply clear metrics until we knew
	 * no one is depending on us, so we need kind of counter
	 * for "ReplayEvent" users.
	 *
	 * What is more complex -- RAW events, if user (for some
	 * reason) will pass some cache event metric with improper
	 * event opcode -- it's fine from hardware point of view
	 * but completely nonsense from "meaning" of such action.
	 *
	 * So at moment let leave metrics turned on forever -- it's
	 * ok for now but need to be revisited!
	 *
	 * (void)checking_wrmsrl(MSR_IA32_PEBS_ENABLE, (u64)0);
	 * (void)checking_wrmsrl(MSR_P4_PEBS_MATRIX_VERT, (u64)0);
	 */
}
