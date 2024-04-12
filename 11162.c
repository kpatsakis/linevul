static void pfault_interrupt(unsigned int ext_int_code,
			     unsigned int param32, unsigned long param64)
{
	struct task_struct *tsk;
	__u16 subcode;
	pid_t pid;

	/*
	 * Get the external interruption subcode & pfault
	 * initial/completion signal bit. VM stores this 
	 * in the 'cpu address' field associated with the
         * external interrupt. 
	 */
	subcode = ext_int_code >> 16;
	if ((subcode & 0xff00) != __SUBCODE_MASK)
		return;
	kstat_cpu(smp_processor_id()).irqs[EXTINT_PFL]++;
	if (subcode & 0x0080) {
		/* Get the token (= pid of the affected task). */
		pid = sizeof(void *) == 4 ? param32 : param64;
		rcu_read_lock();
		tsk = find_task_by_pid_ns(pid, &init_pid_ns);
		if (tsk)
			get_task_struct(tsk);
		rcu_read_unlock();
		if (!tsk)
			return;
	} else {
		tsk = current;
	}
	spin_lock(&pfault_lock);
	if (subcode & 0x0080) {
		/* signal bit is set -> a page has been swapped in by VM */
		if (tsk->thread.pfault_wait == 1) {
			/* Initial interrupt was faster than the completion
			 * interrupt. pfault_wait is valid. Set pfault_wait
			 * back to zero and wake up the process. This can
			 * safely be done because the task is still sleeping
			 * and can't produce new pfaults. */
			tsk->thread.pfault_wait = 0;
			list_del(&tsk->thread.list);
			wake_up_process(tsk);
		} else {
			/* Completion interrupt was faster than initial
			 * interrupt. Set pfault_wait to -1 so the initial
			 * interrupt doesn't put the task to sleep. */
			tsk->thread.pfault_wait = -1;
		}
		put_task_struct(tsk);
	} else {
		/* signal bit not set -> a real page is missing. */
		if (tsk->thread.pfault_wait == -1) {
			/* Completion interrupt was faster than the initial
			 * interrupt (pfault_wait == -1). Set pfault_wait
			 * back to zero and exit. */
			tsk->thread.pfault_wait = 0;
		} else {
			/* Initial interrupt arrived before completion
			 * interrupt. Let the task sleep. */
			tsk->thread.pfault_wait = 1;
			list_add(&tsk->thread.list, &pfault_list);
			set_task_state(tsk, TASK_UNINTERRUPTIBLE);
			set_tsk_need_resched(tsk);
		}
	}
	spin_unlock(&pfault_lock);
}
