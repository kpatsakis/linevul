php_http_url_t *php_http_url_mod(const php_http_url_t *old_url, const php_http_url_t *new_url, unsigned flags TSRMLS_DC)
{
	php_http_url_t *tmp_url = NULL;
	php_http_buffer_t buf;

	php_http_buffer_init_ex(&buf, MAX(PHP_HTTP_BUFFER_DEFAULT_SIZE, sizeof(php_http_url_t)<<2), PHP_HTTP_BUFFER_INIT_PREALLOC);
	php_http_buffer_account(&buf, sizeof(php_http_url_t));
	memset(buf.data, 0, buf.used);

	/* set from env if requested */
	if (flags & PHP_HTTP_URL_FROM_ENV) {
		php_http_url_t *env_url = php_http_url_from_env(TSRMLS_C);

		old_url = tmp_url = php_http_url_mod(env_url, old_url, flags ^ PHP_HTTP_URL_FROM_ENV TSRMLS_CC);
		php_http_url_free(&env_url);
	}

	url_copy(scheme);

	if (!(flags & PHP_HTTP_URL_STRIP_USER)) {
		url_copy(user);
	}

	if (!(flags & PHP_HTTP_URL_STRIP_PASS)) {
		url_copy(pass);
	}
	
	url_copy(host);
	
	if (!(flags & PHP_HTTP_URL_STRIP_PORT)) {
		url(buf)->port = url_isset(new_url, port) ? new_url->port : ((old_url) ? old_url->port : 0);
	}

	if (!(flags & PHP_HTTP_URL_STRIP_PATH)) {
		if ((flags & PHP_HTTP_URL_JOIN_PATH) && url_isset(old_url, path) && url_isset(new_url, path) && *new_url->path != '/') {
			size_t old_path_len = strlen(old_url->path), new_path_len = strlen(new_url->path);
			char *path = ecalloc(1, old_path_len + new_path_len + 1 + 1);
			
			strcat(path, old_url->path);
			if (path[old_path_len - 1] != '/') {
				php_dirname(path, old_path_len);
				strcat(path, "/");
			}
			strcat(path, new_url->path);
			
			url(buf)->path = &buf.data[buf.used];
			if (path[0] != '/') {
				url_append(&buf, php_http_buffer_append(&buf, "/", 1));
			}
			url_append(&buf, php_http_buffer_append(&buf, path, strlen(path) + 1));
			efree(path);
		} else {
			const char *path = NULL;

			if (url_isset(new_url, path)) {
				path = new_url->path;
			} else if (url_isset(old_url, path)) {
				path = old_url->path;
			}

			if (path) {
				url(buf)->path = &buf.data[buf.used];

				url_append(&buf, php_http_buffer_append(&buf, path, strlen(path) + 1));
			}


		}
	}

	if (!(flags & PHP_HTTP_URL_STRIP_QUERY)) {
		if ((flags & PHP_HTTP_URL_JOIN_QUERY) && url_isset(new_url, query) && url_isset(old_url, query)) {
			zval qarr, qstr;
			
			INIT_PZVAL(&qstr);
			INIT_PZVAL(&qarr);
			array_init(&qarr);
			
			ZVAL_STRING(&qstr, old_url->query, 0);
			php_http_querystring_update(&qarr, &qstr, NULL TSRMLS_CC);
			ZVAL_STRING(&qstr, new_url->query, 0);
			php_http_querystring_update(&qarr, &qstr, NULL TSRMLS_CC);
			
			ZVAL_NULL(&qstr);
			php_http_querystring_update(&qarr, NULL, &qstr TSRMLS_CC);

			url(buf)->query = &buf.data[buf.used];
			url_append(&buf, php_http_buffer_append(&buf, Z_STRVAL(qstr), Z_STRLEN(qstr) + 1));

			zval_dtor(&qstr);
			zval_dtor(&qarr);
		} else {
			url_copy(query);
		}
	}

	if (!(flags & PHP_HTTP_URL_STRIP_FRAGMENT)) {
		url_copy(fragment);
	}
	
	/* done with copy & combine & strip */

	if (flags & PHP_HTTP_URL_FROM_ENV) {
		/* free old_url we tainted above */
		php_http_url_free(&tmp_url);
	}

	/* replace directory references if path is not a single slash */
	if ((flags & PHP_HTTP_URL_SANITIZE_PATH)
	&&	url(buf)->path[0] && url(buf)->path[1]) {
		char *ptr, *end = url(buf)->path + strlen(url(buf)->path) + 1;
			
		for (ptr = strchr(url(buf)->path, '/'); ptr; ptr = strchr(ptr, '/')) {
			switch (ptr[1]) {
				case '/':
					memmove(&ptr[1], &ptr[2], end - &ptr[2]);
					break;
					
				case '.':
					switch (ptr[2]) {
						case '\0':
							ptr[1] = '\0';
							break;

						case '/':
							memmove(&ptr[1], &ptr[3], end - &ptr[3]);
							break;

						case '.':
							if (ptr[3] == '/') {
								char *pos = &ptr[4];
								while (ptr != url(buf)->path) {
									if (*--ptr == '/') {
										break;
									}
								}
								memmove(&ptr[1], pos, end - pos);
								break;
							} else if (!ptr[3]) {
								/* .. at the end */
								ptr[1] = '\0';
							}
							/* no break */

						default:
							/* something else */
							++ptr;
							break;
					}
					break;

				default:
					++ptr;
					break;
			}
		}
	}
	/* unset default ports */
	if (url(buf)->port) {
		if (	((url(buf)->port == 80) && url(buf)->scheme && !strcmp(url(buf)->scheme, "http"))
			||	((url(buf)->port ==443) && url(buf)->scheme && !strcmp(url(buf)->scheme, "https"))
		) {
			url(buf)->port = 0;
		}
	}
	
	return url(buf);
}
