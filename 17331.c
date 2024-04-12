static int row_prop_exists(zval *object, zval *member, int check_empty, const zend_literal *key TSRMLS_DC)
{
	pdo_stmt_t * stmt = (pdo_stmt_t *) zend_object_store_get_object(object TSRMLS_CC);
	int colno = -1;

	if (stmt) {
		if (Z_TYPE_P(member) == IS_LONG) {
			return Z_LVAL_P(member) >= 0 && Z_LVAL_P(member) < stmt->column_count;
		} else {
			convert_to_string(member);

			/* TODO: replace this with a hash of available column names to column
			 * numbers */
			for (colno = 0; colno < stmt->column_count; colno++) {
				if (strcmp(stmt->columns[colno].name, Z_STRVAL_P(member)) == 0) {
					int res;
					zval *val;

					MAKE_STD_ZVAL(val);
					fetch_value(stmt, val, colno, NULL TSRMLS_CC);
					res = check_empty ? i_zend_is_true(val) : Z_TYPE_P(val) != IS_NULL;
					zval_ptr_dtor(&val);

					return res;
				}
			}
		}
	}

	return 0;
}
