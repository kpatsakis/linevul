 static void free_statement(pdo_stmt_t *stmt TSRMLS_DC)
{
	if (stmt->bound_params) {
		zend_hash_destroy(stmt->bound_params);
		FREE_HASHTABLE(stmt->bound_params);
		stmt->bound_params = NULL;
	}
	if (stmt->bound_param_map) {
		zend_hash_destroy(stmt->bound_param_map);
		FREE_HASHTABLE(stmt->bound_param_map);
		stmt->bound_param_map = NULL;
	}
	if (stmt->bound_columns) {
		zend_hash_destroy(stmt->bound_columns);
		FREE_HASHTABLE(stmt->bound_columns);
		stmt->bound_columns = NULL;
	}

	if (stmt->methods && stmt->methods->dtor) {
		stmt->methods->dtor(stmt TSRMLS_CC);
	}
	if (stmt->query_string) {
		efree(stmt->query_string);
	}

	if (stmt->columns) {
		int i;
		struct pdo_column_data *cols = stmt->columns;

		for (i = 0; i < stmt->column_count; i++) {
			if (cols[i].name) {
				efree(cols[i].name);
				cols[i].name = NULL;
			}
		}
		efree(stmt->columns);
		stmt->columns = NULL;
	}

	if (stmt->fetch.into && stmt->default_fetch_type == PDO_FETCH_INTO) {
		FREE_ZVAL(stmt->fetch.into);
		stmt->fetch.into = NULL;
	}

	do_fetch_opt_finish(stmt, 1 TSRMLS_CC);

	zend_objects_store_del_ref(&stmt->database_object_handle TSRMLS_CC);
	if (stmt->dbh) {
		php_pdo_dbh_delref(stmt->dbh TSRMLS_CC);
	}
	zend_object_std_dtor(&stmt->std TSRMLS_CC);
	efree(stmt);
}
