static void ipmr_expire_process(unsigned long arg)
{
	struct mr6_table *mrt = (struct mr6_table *)arg;

	if (!spin_trylock(&mfc_unres_lock)) {
		mod_timer(&mrt->ipmr_expire_timer, jiffies + 1);
		return;
	}

	if (!list_empty(&mrt->mfc6_unres_queue))
		ipmr_do_expire_process(mrt);

	spin_unlock(&mfc_unres_lock);
}
