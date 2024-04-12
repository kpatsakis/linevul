PHP_FUNCTION(stream_socket_sendto)
{
	php_stream *stream;
	zval *zstream;
	long flags = 0;
	char *data, *target_addr = NULL;
	int datalen, target_addr_len = 0;
	php_sockaddr_storage sa;
	socklen_t sl = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs|ls", &zstream, &data, &datalen, &flags, &target_addr, &target_addr_len) == FAILURE) {
		RETURN_FALSE;
	}
	php_stream_from_zval(stream, &zstream);

	if (target_addr_len) {
		/* parse the address */
		if (FAILURE == php_network_parse_network_address_with_port(target_addr, target_addr_len, (struct sockaddr*)&sa, &sl TSRMLS_CC)) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to parse `%s' into a valid network address", target_addr);
			RETURN_FALSE;
		}
	}

	RETURN_LONG(php_stream_xport_sendto(stream, data, datalen, flags, target_addr ? &sa : NULL, sl TSRMLS_CC));
}
