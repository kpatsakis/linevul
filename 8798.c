nlmsvc_notify_blocked(struct file_lock *fl)
{
	struct nlm_block	*block;

	dprintk("lockd: VFS unblock notification for block %p\n", fl);
	spin_lock(&nlm_blocked_lock);
	list_for_each_entry(block, &nlm_blocked, b_list) {
		if (nlm_compare_locks(&block->b_call->a_args.lock.fl, fl)) {
			nlmsvc_insert_block_locked(block, 0);
			spin_unlock(&nlm_blocked_lock);
			svc_wake_up(block->b_daemon);
			return;
		}
	}
	spin_unlock(&nlm_blocked_lock);
	printk(KERN_WARNING "lockd: notification for unknown block!\n");
}
