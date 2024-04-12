	__acquires(RCU)
{
	rcu_read_lock();
	return *pos ? ptype_get_idx(*pos - 1) : SEQ_START_TOKEN;
}
