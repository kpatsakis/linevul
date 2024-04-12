static void init_msrpm_offsets(void)
{
	int i;

	memset(msrpm_offsets, 0xff, sizeof(msrpm_offsets));

	for (i = 0; direct_access_msrs[i].index != MSR_INVALID; i++) {
		u32 offset;

		offset = svm_msrpm_offset(direct_access_msrs[i].index);
		BUG_ON(offset == MSR_INVALID);

		add_msr_offset(offset);
	}
}
