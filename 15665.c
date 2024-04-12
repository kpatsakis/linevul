bool param_get_location(
	const char *parameter,
	MyString  &filename,
	int       &line_number)
{
	bool found_it;

	if (parameter != NULL && extra_info != NULL) {
		found_it = extra_info->GetParam(parameter, filename, line_number);
	} else {
		found_it = false;
	}
	return found_it;
}
