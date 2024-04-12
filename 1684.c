static void perf_swevent_del(struct perf_event *event, int flags)
{
	hlist_del_rcu(&event->hlist_entry);
}
