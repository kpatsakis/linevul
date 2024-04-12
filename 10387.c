static int check_stack_boundary(struct verifier_env *env, int regno,
				int access_size, bool zero_size_allowed)
{
	struct verifier_state *state = &env->cur_state;
	struct reg_state *regs = state->regs;
	int off, i;

	if (regs[regno].type != PTR_TO_STACK) {
		if (zero_size_allowed && access_size == 0 &&
		    regs[regno].type == CONST_IMM &&
		    regs[regno].imm  == 0)
			return 0;

		verbose("R%d type=%s expected=%s\n", regno,
			reg_type_str[regs[regno].type],
			reg_type_str[PTR_TO_STACK]);
		return -EACCES;
	}

	off = regs[regno].imm;
	if (off >= 0 || off < -MAX_BPF_STACK || off + access_size > 0 ||
	    access_size <= 0) {
		verbose("invalid stack type R%d off=%d access_size=%d\n",
			regno, off, access_size);
		return -EACCES;
	}

	for (i = 0; i < access_size; i++) {
		if (state->stack_slot_type[MAX_BPF_STACK + off + i] != STACK_MISC) {
			verbose("invalid indirect read from stack off %d+%d size %d\n",
				off, i, access_size);
			return -EACCES;
		}
	}
	return 0;
}
