static inline void vti_set_rr6(unsigned long rr6)
{
	ia64_set_rr(RR6, rr6);
	ia64_srlz_i();
}
