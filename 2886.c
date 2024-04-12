static inline int get_sigset_t(sigset_t *set, const sigset_t __user *uset)
{
	return copy_from_user(set, uset, sizeof(*uset));
}
