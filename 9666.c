bgp_attr_flags_diagnose(struct bgp_attr_parser_args *args,
			uint8_t desired_flags /* how RFC says it must be */
)
{
	uint8_t seen = 0, i;
	uint8_t real_flags = args->flags;
	const uint8_t attr_code = args->type;

	desired_flags &= ~BGP_ATTR_FLAG_EXTLEN;
	real_flags &= ~BGP_ATTR_FLAG_EXTLEN;
	for (i = 0; i <= 2; i++) /* O,T,P, but not E */
		if (CHECK_FLAG(desired_flags, attr_flag_str[i].key)
		    != CHECK_FLAG(real_flags, attr_flag_str[i].key)) {
			flog_err(EC_BGP_ATTR_FLAG,
				 "%s attribute must%s be flagged as \"%s\"",
				 lookup_msg(attr_str, attr_code, NULL),
				 CHECK_FLAG(desired_flags, attr_flag_str[i].key)
					 ? ""
					 : " not",
				 attr_flag_str[i].str);
			seen = 1;
		}
	if (!seen) {
		zlog_debug(
			"Strange, %s called for attr %s, but no problem found with flags"
			" (real flags 0x%x, desired 0x%x)",
			__func__, lookup_msg(attr_str, attr_code, NULL),
			real_flags, desired_flags);
	}
}
