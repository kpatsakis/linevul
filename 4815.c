PHP_FUNCTION(stream_socket_client)
{
	char *host;
	int host_len;
	zval *zerrno = NULL, *zerrstr = NULL, *zcontext = NULL;
	double timeout = FG(default_socket_timeout);
	php_timeout_ull conv;
	struct timeval tv;
	char *hashkey = NULL;
	php_stream *stream = NULL;
	int err;
	long flags = PHP_STREAM_CLIENT_CONNECT;
	char *errstr = NULL;
	php_stream_context *context = NULL;

	RETVAL_FALSE;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|zzdlr", &host, &host_len, &zerrno, &zerrstr, &timeout, &flags, &zcontext) == FAILURE) {
		RETURN_FALSE;
	}

	context = php_stream_context_from_zval(zcontext, flags & PHP_FILE_NO_DEFAULT_CONTEXT);

	if (flags & PHP_STREAM_CLIENT_PERSISTENT) {
		spprintf(&hashkey, 0, "stream_socket_client__%s", host);
	}

	/* prepare the timeout value for use */
	conv = (php_timeout_ull) (timeout * 1000000.0);
#ifdef PHP_WIN32
	tv.tv_sec = (long)(conv / 1000000);
	tv.tv_usec =(long)(conv % 1000000);
#else
	tv.tv_sec = conv / 1000000;
	tv.tv_usec = conv % 1000000;
#endif
	if (zerrno)	{
		zval_dtor(zerrno);
		ZVAL_LONG(zerrno, 0);
	}
	if (zerrstr) {
		zval_dtor(zerrstr);
		ZVAL_STRING(zerrstr, "", 1);
	}

	stream = php_stream_xport_create(host, host_len, REPORT_ERRORS,
			STREAM_XPORT_CLIENT | (flags & PHP_STREAM_CLIENT_CONNECT ? STREAM_XPORT_CONNECT : 0) |
			(flags & PHP_STREAM_CLIENT_ASYNC_CONNECT ? STREAM_XPORT_CONNECT_ASYNC : 0),
			hashkey, &tv, context, &errstr, &err);


	if (stream == NULL) {
		/* host might contain binary characters */
		char *quoted_host = php_addslashes(host, host_len, NULL, 0 TSRMLS_CC);

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "unable to connect to %s (%s)", quoted_host, errstr == NULL ? "Unknown error" : errstr);
		efree(quoted_host);
	}

	if (hashkey) {
		efree(hashkey);
	}

	if (stream == NULL)	{
		if (zerrno) {
			zval_dtor(zerrno);
			ZVAL_LONG(zerrno, err);
		}
		if (zerrstr && errstr) {
			/* no need to dup; we need to efree buf anyway */
			zval_dtor(zerrstr);
			ZVAL_STRING(zerrstr, errstr, 0);
		} else if (errstr) {
			efree(errstr);
		}
		RETURN_FALSE;
	}

	if (errstr) {
		efree(errstr);
	}

	php_stream_to_zval(stream, return_value);

}
