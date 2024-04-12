int pdo_stmt_setup_fetch_mode(INTERNAL_FUNCTION_PARAMETERS, pdo_stmt_t *stmt, int skip)
{
	long mode = PDO_FETCH_BOTH;
	int flags = 0, argc = ZEND_NUM_ARGS() - skip;
	zval ***args;
	zend_class_entry **cep;
	int retval;

	do_fetch_opt_finish(stmt, 1 TSRMLS_CC);

	switch (stmt->default_fetch_type) {
		case PDO_FETCH_INTO:
			if (stmt->fetch.into) {
				zval_ptr_dtor(&stmt->fetch.into);
				stmt->fetch.into = NULL;
			}
			break;
		default:
			;
	}

	stmt->default_fetch_type = PDO_FETCH_BOTH;

	if (argc == 0) {
		return SUCCESS;
	}

	args = safe_emalloc(ZEND_NUM_ARGS(), sizeof(zval*), 0);

	retval = zend_get_parameters_array_ex(ZEND_NUM_ARGS(), args);

	if (SUCCESS == retval) {
		if (Z_TYPE_PP(args[skip]) != IS_LONG) {
			pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "mode must be an integer" TSRMLS_CC);
			retval = FAILURE;
		} else {
			mode = Z_LVAL_PP(args[skip]);
			flags = mode & PDO_FETCH_FLAGS;

			retval = pdo_stmt_verify_mode(stmt, mode, 0 TSRMLS_CC);
		}
	}

	if (FAILURE == retval) {
		PDO_STMT_CLEAR_ERR();
		efree(args);
		return FAILURE;
	}

	retval = FAILURE;
	switch (mode & ~PDO_FETCH_FLAGS) {
		case PDO_FETCH_USE_DEFAULT:
		case PDO_FETCH_LAZY:
		case PDO_FETCH_ASSOC:
		case PDO_FETCH_NUM:
		case PDO_FETCH_BOTH:
		case PDO_FETCH_OBJ:
		case PDO_FETCH_BOUND:
		case PDO_FETCH_NAMED:
		case PDO_FETCH_KEY_PAIR:
			if (argc != 1) {
				pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "fetch mode doesn't allow any extra arguments" TSRMLS_CC);
			} else {
				retval = SUCCESS;
			}
			break;

		case PDO_FETCH_COLUMN:
			if (argc != 2) {
				pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "fetch mode requires the colno argument" TSRMLS_CC);
			} else	if (Z_TYPE_PP(args[skip+1]) != IS_LONG) {
				pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "colno must be an integer" TSRMLS_CC);
			} else {
				stmt->fetch.column = Z_LVAL_PP(args[skip+1]);
				retval = SUCCESS;
			}
			break;

		case PDO_FETCH_CLASS:
			/* Gets its class name from 1st column */
			if ((flags & PDO_FETCH_CLASSTYPE) == PDO_FETCH_CLASSTYPE) {
				if (argc != 1) {
					pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "fetch mode doesn't allow any extra arguments" TSRMLS_CC);
				} else {
					stmt->fetch.cls.ce = NULL;
					retval = SUCCESS;
				}
			} else {
				if (argc < 2) {
					pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "fetch mode requires the classname argument" TSRMLS_CC);
				} else if (argc > 3) {
					pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "too many arguments" TSRMLS_CC);
				} else if (Z_TYPE_PP(args[skip+1]) != IS_STRING) {
					pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "classname must be a string" TSRMLS_CC);
				} else {
					retval = zend_lookup_class(Z_STRVAL_PP(args[skip+1]),
						Z_STRLEN_PP(args[skip+1]), &cep TSRMLS_CC);

					if (SUCCESS == retval && cep && *cep) {
						stmt->fetch.cls.ce = *cep;
					}
				}
			}

			if (SUCCESS == retval) {
				stmt->fetch.cls.ctor_args = NULL;
#ifdef ilia_0 /* we'll only need this when we have persistent statements, if ever */
				if (stmt->dbh->is_persistent) {
					php_error_docref(NULL TSRMLS_CC, E_WARNING, "PHP might crash if you don't call $stmt->setFetchMode() to reset to defaults on this persistent statement.  This will be fixed in a later release");
				}
#endif
				if (argc == 3) {
					if (Z_TYPE_PP(args[skip+2]) != IS_NULL && Z_TYPE_PP(args[skip+2]) != IS_ARRAY) {
						pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "ctor_args must be either NULL or an array" TSRMLS_CC);
						retval = FAILURE;
					} else if (Z_TYPE_PP(args[skip+2]) == IS_ARRAY && zend_hash_num_elements(Z_ARRVAL_PP(args[skip+2]))) {
						ALLOC_ZVAL(stmt->fetch.cls.ctor_args);
						*stmt->fetch.cls.ctor_args = **args[skip+2];
						zval_copy_ctor(stmt->fetch.cls.ctor_args);
					}
				}

				if (SUCCESS == retval) {
					do_fetch_class_prepare(stmt TSRMLS_CC);
				}
			}

			break;

		case PDO_FETCH_INTO:
			if (argc != 2) {
				pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "fetch mode requires the object parameter" TSRMLS_CC);
			} else if (Z_TYPE_PP(args[skip+1]) != IS_OBJECT) {
				pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "object must be an object" TSRMLS_CC);
			} else {
				retval = SUCCESS;
			}

			if (SUCCESS == retval) {
#ifdef ilia_0 /* we'll only need this when we have persistent statements, if ever */
				if (stmt->dbh->is_persistent) {
					php_error_docref(NULL TSRMLS_CC, E_WARNING, "PHP might crash if you don't call $stmt->setFetchMode() to reset to defaults on this persistent statement.  This will be fixed in a later release");
				}
#endif
				MAKE_STD_ZVAL(stmt->fetch.into);

				Z_TYPE_P(stmt->fetch.into) = IS_OBJECT;
				Z_OBJ_HANDLE_P(stmt->fetch.into) = Z_OBJ_HANDLE_PP(args[skip+1]);
				Z_OBJ_HT_P(stmt->fetch.into) = Z_OBJ_HT_PP(args[skip+1]);
				zend_objects_store_add_ref(stmt->fetch.into TSRMLS_CC);
			}

			break;

		default:
			pdo_raise_impl_error(stmt->dbh, stmt, "22003", "Invalid fetch mode specified" TSRMLS_CC);
	}

	if (SUCCESS == retval) {
		stmt->default_fetch_type = mode;
	}

	/*
	 * PDO error (if any) has already been raised at this point.
	 *
	 * The error_code is cleared, otherwise the caller will read the
	 * last error message from the driver.
	 *
	 */
	PDO_STMT_CLEAR_ERR();

	efree(args);

	return retval;
}
