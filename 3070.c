static int set_bdev_super(struct super_block *s, void *data)
{
	s->s_bdev = data;
	s->s_dev = s->s_bdev->bd_dev;

	/*
	 * We set the bdi here to the queue backing, file systems can
	 * overwrite this in ->fill_super()
	 */
	s->s_bdi = &bdev_get_queue(s->s_bdev)->backing_dev_info;
	return 0;
}
