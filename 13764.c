PHP_FUNCTION(get_headers)
{
	char *url;
	int url_len;
	php_stream_context *context;
	php_stream *stream;
	zval **prev_val, **hdr = NULL, **h;
	HashPosition pos;
	HashTable *hashT;
	long format = 0;
                
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &url, &url_len, &format) == FAILURE) {
		return;
	}
	context = FG(default_context) ? FG(default_context) : (FG(default_context) = php_stream_context_alloc(TSRMLS_C));

	if (!(stream = php_stream_open_wrapper_ex(url, "r", REPORT_ERRORS | STREAM_USE_URL | STREAM_ONLY_GET_HEADERS, NULL, context))) {
		RETURN_FALSE;
	}

	if (!stream->wrapperdata || Z_TYPE_P(stream->wrapperdata) != IS_ARRAY) {
		php_stream_close(stream);
		RETURN_FALSE;
	}

	array_init(return_value);

	/* check for curl-wrappers that provide headers via a special "headers" element */
	if (zend_hash_find(HASH_OF(stream->wrapperdata), "headers", sizeof("headers"), (void **)&h) != FAILURE && Z_TYPE_PP(h) == IS_ARRAY) {
		/* curl-wrappers don't load data until the 1st read */ 
		if (!Z_ARRVAL_PP(h)->nNumOfElements) {
			php_stream_getc(stream);
		}
		zend_hash_find(HASH_OF(stream->wrapperdata), "headers", sizeof("headers"), (void **)&h);
		hashT = Z_ARRVAL_PP(h);	
	} else {
		hashT = HASH_OF(stream->wrapperdata);
	}

	zend_hash_internal_pointer_reset_ex(hashT, &pos);
	while (zend_hash_get_current_data_ex(hashT, (void**)&hdr, &pos) != FAILURE) {
		if (!hdr || Z_TYPE_PP(hdr) != IS_STRING) {
			zend_hash_move_forward_ex(hashT, &pos);
			continue;
		}
		if (!format) {
no_name_header:
			add_next_index_stringl(return_value, Z_STRVAL_PP(hdr), Z_STRLEN_PP(hdr), 1);
		} else {
			char c;
			char *s, *p;

			if ((p = strchr(Z_STRVAL_PP(hdr), ':'))) {
				c = *p;
				*p = '\0';
				s = p + 1;
				while (isspace((int)*(unsigned char *)s)) {
					s++;
				}

				if (zend_hash_find(HASH_OF(return_value), Z_STRVAL_PP(hdr), (p - Z_STRVAL_PP(hdr) + 1), (void **) &prev_val) == FAILURE) {
					add_assoc_stringl_ex(return_value, Z_STRVAL_PP(hdr), (p - Z_STRVAL_PP(hdr) + 1), s, (Z_STRLEN_PP(hdr) - (s - Z_STRVAL_PP(hdr))), 1);
				} else { /* some headers may occur more then once, therefor we need to remake the string into an array */
					convert_to_array(*prev_val);
					add_next_index_stringl(*prev_val, s, (Z_STRLEN_PP(hdr) - (s - Z_STRVAL_PP(hdr))), 1);
				}

				*p = c;
			} else {
				goto no_name_header;
			}
		}
		zend_hash_move_forward_ex(hashT, &pos);
	}

	php_stream_close(stream);
}
