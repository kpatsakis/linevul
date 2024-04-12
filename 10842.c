static bool vhost_work_seq_done(struct vhost_dev *dev, struct vhost_work *work,
				unsigned seq)
{
	int left;

	spin_lock_irq(&dev->work_lock);
	left = seq - work->done_seq;
	spin_unlock_irq(&dev->work_lock);
	return left <= 0;
}
