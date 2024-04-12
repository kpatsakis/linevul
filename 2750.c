ZEND_API int zend_fcall_info_argv(zend_fcall_info *fci TSRMLS_DC, int argc, va_list *argv) /* {{{ */
{
	int i;
	zval **arg;

	if (argc < 0) {
		return FAILURE;
	}

	zend_fcall_info_args_clear(fci, !argc);

	if (argc) {
		fci->param_count = argc;
		fci->params = (zval ***) erealloc(fci->params, fci->param_count * sizeof(zval **));

		for (i = 0; i < argc; ++i) {
			arg = va_arg(*argv, zval **);
			fci->params[i] = arg;
		}
	}

	return SUCCESS;
}
/* }}} */
