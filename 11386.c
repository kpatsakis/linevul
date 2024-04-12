void llc_sk_reset(struct sock *sk)
{
	struct llc_sock *llc = llc_sk(sk);

	llc_conn_ac_stop_all_timers(sk, NULL);
	skb_queue_purge(&sk->sk_write_queue);
	skb_queue_purge(&llc->pdu_unack_q);
	llc->remote_busy_flag	= 0;
	llc->cause_flag		= 0;
	llc->retry_count	= 0;
	llc_conn_set_p_flag(sk, 0);
	llc->f_flag		= 0;
	llc->s_flag		= 0;
	llc->ack_pf		= 0;
	llc->first_pdu_Ns	= 0;
	llc->ack_must_be_send	= 0;
	llc->dec_step		= 1;
	llc->inc_cntr		= 2;
	llc->dec_cntr		= 2;
	llc->X			= 0;
	llc->failed_data_req	= 0 ;
	llc->last_nr		= 0;
}
