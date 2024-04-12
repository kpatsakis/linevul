static void check_lifetime(struct work_struct *work)
{
	unsigned long now, next, next_sec, next_sched;
	struct in_ifaddr *ifa;
	struct hlist_node *n;
	int i;

	now = jiffies;
	next = round_jiffies_up(now + ADDR_CHECK_FREQUENCY);

	for (i = 0; i < IN4_ADDR_HSIZE; i++) {
		bool change_needed = false;

		rcu_read_lock();
		hlist_for_each_entry_rcu(ifa, &inet_addr_lst[i], hash) {
			unsigned long age;

			if (ifa->ifa_flags & IFA_F_PERMANENT)
				continue;

			/* We try to batch several events at once. */
			age = (now - ifa->ifa_tstamp +
			       ADDRCONF_TIMER_FUZZ_MINUS) / HZ;

			if (ifa->ifa_valid_lft != INFINITY_LIFE_TIME &&
			    age >= ifa->ifa_valid_lft) {
				change_needed = true;
			} else if (ifa->ifa_preferred_lft ==
				   INFINITY_LIFE_TIME) {
				continue;
			} else if (age >= ifa->ifa_preferred_lft) {
				if (time_before(ifa->ifa_tstamp +
						ifa->ifa_valid_lft * HZ, next))
					next = ifa->ifa_tstamp +
					       ifa->ifa_valid_lft * HZ;

				if (!(ifa->ifa_flags & IFA_F_DEPRECATED))
					change_needed = true;
			} else if (time_before(ifa->ifa_tstamp +
					       ifa->ifa_preferred_lft * HZ,
					       next)) {
				next = ifa->ifa_tstamp +
				       ifa->ifa_preferred_lft * HZ;
			}
		}
		rcu_read_unlock();
		if (!change_needed)
			continue;
		rtnl_lock();
		hlist_for_each_entry_safe(ifa, n, &inet_addr_lst[i], hash) {
			unsigned long age;

			if (ifa->ifa_flags & IFA_F_PERMANENT)
				continue;

			/* We try to batch several events at once. */
			age = (now - ifa->ifa_tstamp +
			       ADDRCONF_TIMER_FUZZ_MINUS) / HZ;

			if (ifa->ifa_valid_lft != INFINITY_LIFE_TIME &&
			    age >= ifa->ifa_valid_lft) {
				struct in_ifaddr **ifap;

				for (ifap = &ifa->ifa_dev->ifa_list;
				     *ifap != NULL; ifap = &(*ifap)->ifa_next) {
					if (*ifap == ifa) {
						inet_del_ifa(ifa->ifa_dev,
							     ifap, 1);
						break;
					}
				}
			} else if (ifa->ifa_preferred_lft !=
				   INFINITY_LIFE_TIME &&
				   age >= ifa->ifa_preferred_lft &&
				   !(ifa->ifa_flags & IFA_F_DEPRECATED)) {
				ifa->ifa_flags |= IFA_F_DEPRECATED;
				rtmsg_ifa(RTM_NEWADDR, ifa, NULL, 0);
			}
		}
		rtnl_unlock();
	}

	next_sec = round_jiffies_up(next);
	next_sched = next;

	/* If rounded timeout is accurate enough, accept it. */
	if (time_before(next_sec, next + ADDRCONF_TIMER_FUZZ))
		next_sched = next_sec;

	now = jiffies;
	/* And minimum interval is ADDRCONF_TIMER_FUZZ_MAX. */
	if (time_before(next_sched, now + ADDRCONF_TIMER_FUZZ_MAX))
		next_sched = now + ADDRCONF_TIMER_FUZZ_MAX;

	queue_delayed_work(system_power_efficient_wq, &check_lifetime_work,
			next_sched - now);
}
