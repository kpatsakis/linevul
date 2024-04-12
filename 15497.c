static inline bool is_gp_fault(u32 intr_info)
{
	return is_exception_n(intr_info, GP_VECTOR);
}
