static void multipath_dtr(struct dm_target *ti)
{
	struct multipath *m = ti->private;

	flush_multipath_work(m);
	free_multipath(m);
}
