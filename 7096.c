static void efx_fill_test(unsigned int test_index,
			  struct ethtool_string *strings, u64 *data,
			  int *test, const char *unit_format, int unit_id,
			  const char *test_format, const char *test_id)
{
	struct ethtool_string unit_str, test_str;

	/* Fill data value, if applicable */
	if (data)
		data[test_index] = *test;

	/* Fill string, if applicable */
	if (strings) {
		if (strchr(unit_format, '%'))
			snprintf(unit_str.name, sizeof(unit_str.name),
				 unit_format, unit_id);
		else
			strcpy(unit_str.name, unit_format);
		snprintf(test_str.name, sizeof(test_str.name),
			 test_format, test_id);
		snprintf(strings[test_index].name,
			 sizeof(strings[test_index].name),
			 "%-6s %-24s", unit_str.name, test_str.name);
	}
}
