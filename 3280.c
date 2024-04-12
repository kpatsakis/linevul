static void resched_task(struct task_struct *p)
{
	assert_raw_spin_locked(&task_rq(p)->lock);
	set_tsk_need_resched(p);
}
