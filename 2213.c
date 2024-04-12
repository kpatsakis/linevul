PHP_PGSQL_API int php_pgsql_update(PGconn *pg_link, const char *table, zval *var_array, zval *ids_array, ulong opt, char **sql TSRMLS_DC) 
{
	zval *var_converted = NULL, *ids_converted = NULL;
	smart_str querystr = {0};
	int ret = FAILURE;

	assert(pg_link != NULL);
	assert(table != NULL);
	assert(Z_TYPE_P(var_array) == IS_ARRAY);
	assert(Z_TYPE_P(ids_array) == IS_ARRAY);
	assert(!(opt & ~(PGSQL_CONV_OPTS|PGSQL_DML_NO_CONV|PGSQL_DML_EXEC|PGSQL_DML_STRING)));

	if (zend_hash_num_elements(Z_ARRVAL_P(var_array)) == 0
			|| zend_hash_num_elements(Z_ARRVAL_P(ids_array)) == 0) {
		return FAILURE;
	}

	if (!(opt & PGSQL_DML_NO_CONV)) {
		MAKE_STD_ZVAL(var_converted);
		array_init(var_converted);
		if (php_pgsql_convert(pg_link, table, var_array, var_converted, (opt & PGSQL_CONV_OPTS) TSRMLS_CC) == FAILURE) {
			goto cleanup;
		}
		var_array = var_converted;
		MAKE_STD_ZVAL(ids_converted);
		array_init(ids_converted);
		if (php_pgsql_convert(pg_link, table, ids_array, ids_converted, (opt & PGSQL_CONV_OPTS) TSRMLS_CC) == FAILURE) {
			goto cleanup;
		}
		ids_array = ids_converted;
	}

	smart_str_appends(&querystr, "UPDATE ");
	build_tablename(&querystr, pg_link, table);
	smart_str_appends(&querystr, " SET ");

	if (build_assignment_string(&querystr, Z_ARRVAL_P(var_array), 0, ",", 1 TSRMLS_CC))
		goto cleanup;
	
	smart_str_appends(&querystr, " WHERE ");
	
	if (build_assignment_string(&querystr, Z_ARRVAL_P(ids_array), 1, " AND ", sizeof(" AND ")-1 TSRMLS_CC))
		goto cleanup;

	smart_str_appendc(&querystr, ';');	
	smart_str_0(&querystr);

	if ((opt & PGSQL_DML_EXEC) && do_exec(&querystr, PGRES_COMMAND_OK, pg_link, opt TSRMLS_CC) == 0) {
		ret = SUCCESS;
	} else if (opt & PGSQL_DML_STRING) {
		ret = SUCCESS;
	}

cleanup:
	if (var_converted) {
		zval_dtor(var_converted);
		FREE_ZVAL(var_converted);
	}
	if (ids_converted) {
		zval_dtor(ids_converted);
		FREE_ZVAL(ids_converted);
	}
	if (ret == SUCCESS && (opt & PGSQL_DML_STRING)) {
		*sql = querystr.c;
	}
	else {
		smart_str_free(&querystr);
	}
	return ret;
}
