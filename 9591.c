static inline bool is_icebp(u32 intr_info)
{
	return (intr_info & (INTR_INFO_INTR_TYPE_MASK | INTR_INFO_VALID_MASK))
		== (INTR_TYPE_PRIV_SW_EXCEPTION | INTR_INFO_VALID_MASK);
}
