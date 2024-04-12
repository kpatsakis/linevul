get_exclude_regex(Regex &excludeFilesRegex)
{
	const char* _errstr;
	int _erroffset;
	char* excludeRegex = param("LOCAL_CONFIG_DIR_EXCLUDE_REGEXP");
	if(excludeRegex) {
		if (!excludeFilesRegex.compile(excludeRegex,
									&_errstr, &_erroffset)) {
			EXCEPT("LOCAL_CONFIG_DIR_EXCLUDE_REGEXP "
				   "config parameter is not a valid "
				   "regular expression.  Value: %s,  Error: %s",
				   excludeRegex, _errstr ? _errstr : "");
		}
		if(!excludeFilesRegex.isInitialized() ) {
			EXCEPT("Could not init regex "
				   "to exclude files in %s\n", __FILE__);
		}
	}
	free(excludeRegex);
}
