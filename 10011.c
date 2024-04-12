static int check_reg_arg(struct bpf_verifier_env *env, u32 regno,
			 enum reg_arg_type t)
{
	struct bpf_reg_state *regs = env->cur_state->regs;

	if (regno >= MAX_BPF_REG) {
		verbose(env, "R%d is invalid\n", regno);
		return -EINVAL;
	}

	if (t == SRC_OP) {
		/* check whether register used as source operand can be read */
		if (regs[regno].type == NOT_INIT) {
			verbose(env, "R%d !read_ok\n", regno);
			return -EACCES;
		}
		mark_reg_read(env->cur_state, regno);
	} else {
		/* check whether register used as dest operand can be written to */
		if (regno == BPF_REG_FP) {
			verbose(env, "frame pointer is read only\n");
			return -EACCES;
		}
		regs[regno].live |= REG_LIVE_WRITTEN;
		if (t == DST_OP)
			mark_reg_unknown(env, regs, regno);
	}
	return 0;
}
