PHP_FUNCTION(linkinfo)
{
	char *link;
	char *dirname;
	int link_len, dir_len;
	struct stat sb;
	int ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "p", &link, &link_len) == FAILURE) {
		return;
	}

	dirname = estrndup(link, link_len);
	dir_len = php_dirname(dirname, link_len);

	if (php_check_open_basedir(dirname TSRMLS_CC)) {
		efree(dirname);
		RETURN_FALSE;
	}

	ret = VCWD_LSTAT(link, &sb);
	if (ret == -1) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", strerror(errno));
		efree(dirname);
		RETURN_LONG(-1L);
	}

	efree(dirname);
	RETURN_LONG((long) sb.st_dev);
}
