void bpf_prog_put(struct bpf_prog *prog)
{
	if (atomic_dec_and_test(&prog->aux->refcnt))
		__prog_put_common(&prog->aux->rcu);
}
