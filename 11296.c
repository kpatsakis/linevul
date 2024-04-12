static PHP_METHOD(PDOStatement, execute)
{
	zval *input_params = NULL;
	int ret = 1;
	PHP_STMT_GET_OBJ;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a!", &input_params)) {
		RETURN_FALSE;
	}

	PDO_STMT_CLEAR_ERR();

	if (input_params) {
		struct pdo_bound_param_data param;
		zval **tmp;
		uint str_length;
		ulong num_index;

		if (stmt->bound_params) {
			zend_hash_destroy(stmt->bound_params);
			FREE_HASHTABLE(stmt->bound_params);
			stmt->bound_params = NULL;
		}

		zend_hash_internal_pointer_reset(Z_ARRVAL_P(input_params));
		while (SUCCESS == zend_hash_get_current_data(Z_ARRVAL_P(input_params), (void*)&tmp)) {
			memset(&param, 0, sizeof(param));

			if (HASH_KEY_IS_STRING == zend_hash_get_current_key_ex(Z_ARRVAL_P(input_params),
						&param.name, &str_length, &num_index, 0, NULL)) {
				/* yes this is correct.  we don't want to count the null byte.  ask wez */
				param.namelen = str_length - 1;
				param.paramno = -1;
			} else {
				/* we're okay to be zero based here */
				if (num_index < 0) {
					pdo_raise_impl_error(stmt->dbh, stmt, "HY093", NULL TSRMLS_CC);
					RETURN_FALSE;
				}
				param.paramno = num_index;
			}

			param.param_type = PDO_PARAM_STR;
			MAKE_STD_ZVAL(param.parameter);
			MAKE_COPY_ZVAL(tmp, param.parameter);

			if (!really_register_bound_param(&param, stmt, 1 TSRMLS_CC)) {
				if (param.parameter) {
					zval_ptr_dtor(&param.parameter);
				}
				RETURN_FALSE;
			}

			zend_hash_move_forward(Z_ARRVAL_P(input_params));
		}
	}

	if (PDO_PLACEHOLDER_NONE == stmt->supports_placeholders) {
		/* handle the emulated parameter binding,
         * stmt->active_query_string holds the query with binds expanded and
		 * quoted.
         */

		ret = pdo_parse_params(stmt, stmt->query_string, stmt->query_stringlen,
			&stmt->active_query_string, &stmt->active_query_stringlen TSRMLS_CC);

		if (ret == 0) {
			/* no changes were made */
			stmt->active_query_string = stmt->query_string;
			stmt->active_query_stringlen = stmt->query_stringlen;
			ret = 1;
		} else if (ret == -1) {
			/* something broke */
			PDO_HANDLE_STMT_ERR();
			RETURN_FALSE;
		}
	} else if (!dispatch_param_event(stmt, PDO_PARAM_EVT_EXEC_PRE TSRMLS_CC)) {
		PDO_HANDLE_STMT_ERR();
		RETURN_FALSE;
	}
	if (stmt->methods->executer(stmt TSRMLS_CC)) {
		if (stmt->active_query_string && stmt->active_query_string != stmt->query_string) {
			efree(stmt->active_query_string);
		}
		stmt->active_query_string = NULL;
		if (!stmt->executed) {
			/* this is the first execute */

			if (stmt->dbh->alloc_own_columns && !stmt->columns) {
				/* for "big boy" drivers, we need to allocate memory to fetch
				 * the results into, so lets do that now */
				ret = pdo_stmt_describe_columns(stmt TSRMLS_CC);
			}

			stmt->executed = 1;
		}

		if (ret && !dispatch_param_event(stmt, PDO_PARAM_EVT_EXEC_POST TSRMLS_CC)) {
			RETURN_FALSE;
		}

		RETURN_BOOL(ret);
	}
	if (stmt->active_query_string && stmt->active_query_string != stmt->query_string) {
		efree(stmt->active_query_string);
	}
	stmt->active_query_string = NULL;
	PDO_HANDLE_STMT_ERR();
	RETURN_FALSE;
}
