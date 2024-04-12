static void sctp_cmd_t1_timer_update(struct sctp_association *asoc,
				    sctp_event_timeout_t timer,
				    char *name)
{
	struct sctp_transport *t;

	t = asoc->init_last_sent_to;
	asoc->init_err_counter++;

	if (t->init_sent_count > (asoc->init_cycle + 1)) {
		asoc->timeouts[timer] *= 2;
		if (asoc->timeouts[timer] > asoc->max_init_timeo) {
			asoc->timeouts[timer] = asoc->max_init_timeo;
		}
		asoc->init_cycle++;

		pr_debug("%s: T1[%s] timeout adjustment init_err_counter:%d"
			 " cycle:%d timeout:%ld\n", __func__, name,
			 asoc->init_err_counter, asoc->init_cycle,
			 asoc->timeouts[timer]);
	}

}
