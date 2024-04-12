json_extract_path(PG_FUNCTION_ARGS)
{
	return get_path_all(fcinfo, false);
}
