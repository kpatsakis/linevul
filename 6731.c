static unsigned long read_pmc(int idx)
{
	unsigned long val;

	switch (idx) {
	case 0:
		val = mfpmr(PMRN_PMC0);
		break;
	case 1:
		val = mfpmr(PMRN_PMC1);
		break;
	case 2:
		val = mfpmr(PMRN_PMC2);
		break;
	case 3:
		val = mfpmr(PMRN_PMC3);
		break;
	default:
		printk(KERN_ERR "oops trying to read PMC%d\n", idx);
		val = 0;
	}
	return val;
}
