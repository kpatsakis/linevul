static int sched_feat_show(struct seq_file *m, void *v)
{
	int i;

	for (i = 0; sched_feat_names[i]; i++) {
		if (!(sysctl_sched_features & (1UL << i)))
			seq_puts(m, "NO_");
		seq_printf(m, "%s ", sched_feat_names[i]);
	}
	seq_puts(m, "\n");

	return 0;
}
