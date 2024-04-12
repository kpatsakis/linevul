perf_event_ctx_lock_nested(struct perf_event *event, int nesting)
{
	struct perf_event_context *ctx;

again:
	rcu_read_lock();
	ctx = ACCESS_ONCE(event->ctx);
	if (!atomic_inc_not_zero(&ctx->refcount)) {
		rcu_read_unlock();
		goto again;
	}
	rcu_read_unlock();

	mutex_lock_nested(&ctx->mutex, nesting);
	if (event->ctx != ctx) {
		mutex_unlock(&ctx->mutex);
		put_ctx(ctx);
		goto again;
	}

	return ctx;
}
