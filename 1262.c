void llc_sap_remove_socket(struct llc_sap *sap, struct sock *sk)
{
	struct llc_sock *llc = llc_sk(sk);

	spin_lock_bh(&sap->sk_lock);
	sk_nulls_del_node_init_rcu(sk);
	hlist_del(&llc->dev_hash_node);
	sap->sk_count--;
	spin_unlock_bh(&sap->sk_lock);
	llc_sap_put(sap);
}
