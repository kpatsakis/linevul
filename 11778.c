static int timerfd_release(struct inode *inode, struct file *file)
{
	struct timerfd_ctx *ctx = file->private_data;

	timerfd_remove_cancel(ctx);

	if (isalarm(ctx))
		alarm_cancel(&ctx->t.alarm);
	else
		hrtimer_cancel(&ctx->t.tmr);
	kfree_rcu(ctx, rcu);
	return 0;
}
