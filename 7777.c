static int do_timerfd_gettime(int ufd, struct itimerspec *t)
{
	struct fd f;
	struct timerfd_ctx *ctx;
	int ret = timerfd_fget(ufd, &f);
	if (ret)
		return ret;
	ctx = f.file->private_data;

	spin_lock_irq(&ctx->wqh.lock);
	if (ctx->expired && ctx->tintv) {
		ctx->expired = 0;

		if (isalarm(ctx)) {
			ctx->ticks +=
				alarm_forward_now(
					&ctx->t.alarm, ctx->tintv) - 1;
			alarm_restart(&ctx->t.alarm);
		} else {
			ctx->ticks +=
				hrtimer_forward_now(&ctx->t.tmr, ctx->tintv)
				- 1;
			hrtimer_restart(&ctx->t.tmr);
		}
	}
	t->it_value = ktime_to_timespec(timerfd_get_remaining(ctx));
	t->it_interval = ktime_to_timespec(ctx->tintv);
	spin_unlock_irq(&ctx->wqh.lock);
	fdput(f);
	return 0;
}
