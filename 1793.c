int register_fsl_emb_pmu(struct fsl_emb_pmu *pmu)
{
	if (ppmu)
		return -EBUSY;		/* something's already registered */

	ppmu = pmu;
	pr_info("%s performance monitor hardware support registered\n",
		pmu->name);

	perf_pmu_register(&fsl_emb_pmu, "cpu", PERF_TYPE_RAW);

	return 0;
}
