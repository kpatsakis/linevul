static int __init perf_workqueue_init(void)
{
	perf_wq = create_singlethread_workqueue("perf");
	WARN(!perf_wq, "failed to create perf workqueue\n");
	return perf_wq ? 0 : -1;
}
