int bpf_analyzer(struct bpf_prog *prog, const struct bpf_ext_analyzer_ops *ops,
		 void *priv)
{
	struct bpf_verifier_env *env;
	int ret;

	env = kzalloc(sizeof(struct bpf_verifier_env), GFP_KERNEL);
	if (!env)
		return -ENOMEM;

	env->insn_aux_data = vzalloc(sizeof(struct bpf_insn_aux_data) *
				     prog->len);
	ret = -ENOMEM;
	if (!env->insn_aux_data)
		goto err_free_env;
	env->prog = prog;
	env->analyzer_ops = ops;
	env->analyzer_priv = priv;

	/* grab the mutex to protect few globals used by verifier */
	mutex_lock(&bpf_verifier_lock);

	log_level = 0;

	env->explored_states = kcalloc(env->prog->len,
				       sizeof(struct bpf_verifier_state_list *),
				       GFP_KERNEL);
	ret = -ENOMEM;
	if (!env->explored_states)
		goto skip_full_check;

	ret = check_cfg(env);
	if (ret < 0)
		goto skip_full_check;

	env->allow_ptr_leaks = capable(CAP_SYS_ADMIN);

	ret = do_check(env);

skip_full_check:
	while (pop_stack(env, NULL) >= 0);
	free_states(env);

	mutex_unlock(&bpf_verifier_lock);
	vfree(env->insn_aux_data);
err_free_env:
	kfree(env);
	return ret;
}
