param_boolean_crufty( const char *name, bool default_value )
{
	char *tmp = param(name);
	if (tmp) {
		char c = *tmp;
		free(tmp);

		if ('t' == c || 'T' == c) {
			return true;
		} else if ('f' == c || 'F' == c) {
			return false;
		} else {
			return param_boolean(name, default_value);
		}
	} else {
		return param_boolean(name, default_value);
	}
}
