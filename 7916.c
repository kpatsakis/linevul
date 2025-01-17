SYSCALL_DEFINE5(perf_event_open,
		struct perf_event_attr __user *, attr_uptr,
		pid_t, pid, int, cpu, int, group_fd, unsigned long, flags)
{
	struct perf_event *group_leader = NULL, *output_event = NULL;
	struct perf_event *event, *sibling;
	struct perf_event_attr attr;
	struct perf_event_context *ctx;
	struct file *event_file = NULL;
	struct file *group_file = NULL;
	struct task_struct *task = NULL;
	struct pmu *pmu;
	int event_fd;
	int move_group = 0;
	int fput_needed = 0;
	int err;

	/* for future expandability... */
	if (flags & ~PERF_FLAG_ALL)
		return -EINVAL;

	err = perf_copy_attr(attr_uptr, &attr);
	if (err)
		return err;

	if (!attr.exclude_kernel) {
		if (perf_paranoid_kernel() && !capable(CAP_SYS_ADMIN))
			return -EACCES;
	}

	if (attr.freq) {
		if (attr.sample_freq > sysctl_perf_event_sample_rate)
			return -EINVAL;
	}

	/*
	 * In cgroup mode, the pid argument is used to pass the fd
	 * opened to the cgroup directory in cgroupfs. The cpu argument
	 * designates the cpu on which to monitor threads from that
	 * cgroup.
	 */
	if ((flags & PERF_FLAG_PID_CGROUP) && (pid == -1 || cpu == -1))
		return -EINVAL;

	event_fd = get_unused_fd_flags(O_RDWR);
	if (event_fd < 0)
		return event_fd;

	if (group_fd != -1) {
		group_leader = perf_fget_light(group_fd, &fput_needed);
		if (IS_ERR(group_leader)) {
			err = PTR_ERR(group_leader);
			goto err_fd;
		}
		group_file = group_leader->filp;
		if (flags & PERF_FLAG_FD_OUTPUT)
			output_event = group_leader;
		if (flags & PERF_FLAG_FD_NO_GROUP)
			group_leader = NULL;
	}

	if (pid != -1 && !(flags & PERF_FLAG_PID_CGROUP)) {
		task = find_lively_task_by_vpid(pid);
		if (IS_ERR(task)) {
			err = PTR_ERR(task);
			goto err_group_fd;
		}
	}

	event = perf_event_alloc(&attr, cpu, task, group_leader, NULL, NULL);
	if (IS_ERR(event)) {
		err = PTR_ERR(event);
		goto err_task;
	}

	if (flags & PERF_FLAG_PID_CGROUP) {
		err = perf_cgroup_connect(pid, event, &attr, group_leader);
		if (err)
			goto err_alloc;
		/*
		 * one more event:
		 * - that has cgroup constraint on event->cpu
		 * - that may need work on context switch
		 */
		atomic_inc(&per_cpu(perf_cgroup_events, event->cpu));
		jump_label_inc(&perf_sched_events);
	}

	/*
	 * Special case software events and allow them to be part of
	 * any hardware group.
	 */
	pmu = event->pmu;

	if (group_leader &&
	    (is_software_event(event) != is_software_event(group_leader))) {
		if (is_software_event(event)) {
			/*
			 * If event and group_leader are not both a software
			 * event, and event is, then group leader is not.
			 *
			 * Allow the addition of software events to !software
			 * groups, this is safe because software events never
			 * fail to schedule.
			 */
			pmu = group_leader->pmu;
		} else if (is_software_event(group_leader) &&
			   (group_leader->group_flags & PERF_GROUP_SOFTWARE)) {
			/*
			 * In case the group is a pure software group, and we
			 * try to add a hardware event, move the whole group to
			 * the hardware context.
			 */
			move_group = 1;
		}
	}

	/*
	 * Get the target context (task or percpu):
	 */
	ctx = find_get_context(pmu, task, cpu);
	if (IS_ERR(ctx)) {
		err = PTR_ERR(ctx);
		goto err_alloc;
	}

	if (task) {
		put_task_struct(task);
		task = NULL;
	}

	/*
	 * Look up the group leader (we will attach this event to it):
	 */
	if (group_leader) {
		err = -EINVAL;

		/*
		 * Do not allow a recursive hierarchy (this new sibling
		 * becoming part of another group-sibling):
		 */
		if (group_leader->group_leader != group_leader)
			goto err_context;
		/*
		 * Do not allow to attach to a group in a different
		 * task or CPU context:
		 */
		if (move_group) {
			if (group_leader->ctx->type != ctx->type)
				goto err_context;
		} else {
			if (group_leader->ctx != ctx)
				goto err_context;
		}

		/*
		 * Only a group leader can be exclusive or pinned
		 */
		if (attr.exclusive || attr.pinned)
			goto err_context;
	}

	if (output_event) {
		err = perf_event_set_output(event, output_event);
		if (err)
			goto err_context;
	}

	event_file = anon_inode_getfile("[perf_event]", &perf_fops, event, O_RDWR);
	if (IS_ERR(event_file)) {
		err = PTR_ERR(event_file);
		goto err_context;
	}

	if (move_group) {
		struct perf_event_context *gctx = group_leader->ctx;

		mutex_lock(&gctx->mutex);
		perf_remove_from_context(group_leader);
		list_for_each_entry(sibling, &group_leader->sibling_list,
				    group_entry) {
			perf_remove_from_context(sibling);
			put_ctx(gctx);
		}
		mutex_unlock(&gctx->mutex);
		put_ctx(gctx);
	}

	event->filp = event_file;
	WARN_ON_ONCE(ctx->parent_ctx);
	mutex_lock(&ctx->mutex);

	if (move_group) {
		perf_install_in_context(ctx, group_leader, cpu);
		get_ctx(ctx);
		list_for_each_entry(sibling, &group_leader->sibling_list,
				    group_entry) {
			perf_install_in_context(ctx, sibling, cpu);
			get_ctx(ctx);
		}
	}

	perf_install_in_context(ctx, event, cpu);
	++ctx->generation;
	perf_unpin_context(ctx);
	mutex_unlock(&ctx->mutex);

	event->owner = current;

	mutex_lock(&current->perf_event_mutex);
	list_add_tail(&event->owner_entry, &current->perf_event_list);
	mutex_unlock(&current->perf_event_mutex);

	/*
	 * Precalculate sample_data sizes
	 */
	perf_event__header_size(event);
	perf_event__id_header_size(event);

	/*
	 * Drop the reference on the group_event after placing the
	 * new event on the sibling_list. This ensures destruction
	 * of the group leader will find the pointer to itself in
	 * perf_group_detach().
	 */
	fput_light(group_file, fput_needed);
	fd_install(event_fd, event_file);
	return event_fd;

err_context:
	perf_unpin_context(ctx);
	put_ctx(ctx);
err_alloc:
	free_event(event);
err_task:
	if (task)
		put_task_struct(task);
err_group_fd:
	fput_light(group_file, fput_needed);
err_fd:
	put_unused_fd(event_fd);
	return err;
}
