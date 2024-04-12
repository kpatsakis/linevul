static inline bool is_no_device(u32 intr_info)
{
	return is_exception_n(intr_info, NM_VECTOR);
}
