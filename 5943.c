PHP_PGSQL_API int php_pgsql_convert(PGconn *pg_link, const char *table_name, const zval *values, zval *result, ulong opt TSRMLS_DC) 
{
	HashPosition pos;
	char *field = NULL;
	uint field_len = -1;
	ulong num_idx = -1;
	zval *meta, **def, **type, **not_null, **has_default, **is_enum, **val, *new_val;
	int key_type, err = 0, skip_field;
	php_pgsql_data_type data_type;

	assert(pg_link != NULL);
	assert(Z_TYPE_P(values) == IS_ARRAY);
	assert(Z_TYPE_P(result) == IS_ARRAY);
	assert(!(opt & ~PGSQL_CONV_OPTS));

	if (!table_name) {
		return FAILURE;
	}
	MAKE_STD_ZVAL(meta);
	array_init(meta);

/* table_name is escaped by php_pgsql_meta_data */
	if (php_pgsql_meta_data(pg_link, table_name, meta TSRMLS_CC) == FAILURE) {
		zval_dtor(meta);
		FREE_ZVAL(meta);
		return FAILURE;
	}
	for (zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(values), &pos);
		 zend_hash_get_current_data_ex(Z_ARRVAL_P(values), (void **)&val, &pos) == SUCCESS;
		 zend_hash_move_forward_ex(Z_ARRVAL_P(values), &pos)) {
		skip_field = 0;
		new_val = NULL;

		if ((key_type = zend_hash_get_current_key_ex(Z_ARRVAL_P(values), &field, &field_len, &num_idx, 0, &pos)) == HASH_KEY_NON_EXISTANT) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to get array key type");
			err = 1;
		}
		if (!err && key_type == HASH_KEY_IS_LONG) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Accepts only string key for values");
			err = 1;
		}
		if (!err && key_type == HASH_KEY_NON_EXISTANT) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Accepts only string key for values");
			err = 1;
		}
		if (!err && zend_hash_find(Z_ARRVAL_P(meta), field, field_len, (void **)&def) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Invalid field name (%s) in values", field);
			err = 1;
		}
		if (!err && zend_hash_find(Z_ARRVAL_PP(def), "type", sizeof("type"), (void **)&type) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Detected broken meta data. Missing 'type'");
			err = 1;
		}
		if (!err && zend_hash_find(Z_ARRVAL_PP(def), "not null", sizeof("not null"), (void **)&not_null) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Detected broken meta data. Missing 'not null'");
			err = 1;
		}
		if (!err && zend_hash_find(Z_ARRVAL_PP(def), "has default", sizeof("has default"), (void **)&has_default) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Detected broken meta data. Missing 'has default'");
			err = 1;
		}
		if (!err && zend_hash_find(Z_ARRVAL_PP(def), "is enum", sizeof("is enum"), (void **)&is_enum) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Detected broken meta data. Missing 'is enum'");
			err = 1;
		}
		if (!err && (Z_TYPE_PP(val) == IS_ARRAY ||
			 Z_TYPE_PP(val) == IS_OBJECT ||
			 Z_TYPE_PP(val) == IS_CONSTANT_ARRAY)) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects scalar values as field values");
			err = 1;
		}
		if (err) {
			break; /* break out for() */
		}
		ALLOC_INIT_ZVAL(new_val);

		if (Z_BVAL_PP(is_enum)) {
			/* enums need to be treated like strings */
			data_type = PG_TEXT;
		}
		else {
			data_type = php_pgsql_get_data_type(Z_STRVAL_PP(type), Z_STRLEN_PP(type));
		}

		switch(data_type)
		{
			case PG_BOOL:
				switch (Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {
							if (!strcmp(Z_STRVAL_PP(val), "t") || !strcmp(Z_STRVAL_PP(val), "T") ||
								!strcmp(Z_STRVAL_PP(val), "y") || !strcmp(Z_STRVAL_PP(val), "Y") ||
								!strcmp(Z_STRVAL_PP(val), "true") || !strcmp(Z_STRVAL_PP(val), "True") ||
								!strcmp(Z_STRVAL_PP(val), "yes") || !strcmp(Z_STRVAL_PP(val), "Yes") ||
								!strcmp(Z_STRVAL_PP(val), "1")) {
								ZVAL_STRING(new_val, "'t'", 1);
							}
							else if (!strcmp(Z_STRVAL_PP(val), "f") || !strcmp(Z_STRVAL_PP(val), "F") ||
									 !strcmp(Z_STRVAL_PP(val), "n") || !strcmp(Z_STRVAL_PP(val), "N") ||
									 !strcmp(Z_STRVAL_PP(val), "false") ||  !strcmp(Z_STRVAL_PP(val), "False") ||
									 !strcmp(Z_STRVAL_PP(val), "no") ||  !strcmp(Z_STRVAL_PP(val), "No") ||
									 !strcmp(Z_STRVAL_PP(val), "0")) {
								ZVAL_STRING(new_val, "'f'", 1);
							}
							else {
								php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Detected invalid value (%s) for PostgreSQL %s field (%s)", Z_STRVAL_PP(val), Z_STRVAL_PP(type), field);
								err = 1;
							}
						}
						break;

					case IS_LONG:
					case IS_BOOL:
						if (Z_LVAL_PP(val)) {
							ZVAL_STRING(new_val, "'t'", 1);
						}
						else {
							ZVAL_STRING(new_val, "'f'", 1);
						}
						break;

					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects string, null, long or boolelan value for PostgreSQL '%s' (%s)", Z_STRVAL_PP(type), field);
				}
				break;

			case PG_OID:
			case PG_INT2:
			case PG_INT4:
			case PG_INT8:
				switch (Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {
							/* FIXME: better regex must be used */
							if (php_pgsql_convert_match(Z_STRVAL_PP(val), Z_STRLEN_PP(val), "^([+-]{0,1}[0-9]+)$", 0 TSRMLS_CC) == FAILURE) {
								err = 1;
							}
							else {
								ZVAL_STRING(new_val, Z_STRVAL_PP(val), 1);
							}
						}
						break;

					case IS_DOUBLE:
						ZVAL_DOUBLE(new_val, Z_DVAL_PP(val));
						convert_to_long_ex(&new_val);
						break;
						
					case IS_LONG:
						ZVAL_LONG(new_val, Z_LVAL_PP(val));
						break;
						
					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL, string, long or double value for pgsql '%s' (%s)", Z_STRVAL_PP(type), field);
				}
				break;

			case PG_NUMERIC:
			case PG_MONEY:
			case PG_FLOAT4:
			case PG_FLOAT8:
				switch (Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {
							/* FIXME: better regex must be used */
							if (php_pgsql_convert_match(Z_STRVAL_PP(val), Z_STRLEN_PP(val), "^([+-]{0,1}[0-9]+)|([+-]{0,1}[0-9]*[\\.][0-9]+)|([+-]{0,1}[0-9]+[\\.][0-9]*)$", 0 TSRMLS_CC) == FAILURE) {
								err = 1;
							}
							else {
								ZVAL_STRING(new_val, Z_STRVAL_PP(val), 1);
							}
						}
						break;

					case IS_LONG:
						ZVAL_LONG(new_val, Z_LVAL_PP(val));
						break;

					case IS_DOUBLE:
						ZVAL_DOUBLE(new_val, Z_DVAL_PP(val));
						break;

					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL, string, long or double value for PostgreSQL '%s' (%s)", Z_STRVAL_PP(type), field);
				}
				break;

			case PG_TEXT:
			case PG_CHAR:
			case PG_VARCHAR:
				switch (Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							if (opt & PGSQL_CONV_FORCE_NULL) {
								ZVAL_STRING(new_val, "NULL", 1);
							} else {
								ZVAL_STRING(new_val, "''", 1);
							}
						}
						else {
							char *tmp;
							Z_TYPE_P(new_val) = IS_STRING;
							tmp = (char *)safe_emalloc(Z_STRLEN_PP(val), 2, 1);
							Z_STRLEN_P(new_val) = (int)PQescapeStringConn(pg_link, tmp, Z_STRVAL_PP(val), Z_STRLEN_PP(val), NULL);
							Z_STRVAL_P(new_val) = tmp;
							php_pgsql_add_quotes(new_val, 1 TSRMLS_CC);
						}
						break;

					case IS_LONG:
						ZVAL_LONG(new_val, Z_LVAL_PP(val));
						convert_to_string_ex(&new_val);
						break;

					case IS_DOUBLE:
						ZVAL_DOUBLE(new_val, Z_DVAL_PP(val));
						convert_to_string_ex(&new_val);
						break;

					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL, string, long or double value for PostgreSQL '%s' (%s)", Z_STRVAL_PP(type), field);
				}
				break;

			case PG_UNIX_TIME:
			case PG_UNIX_TIME_INTERVAL:
				/* these are the actallay a integer */
				switch (Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {
							/* FIXME: Better regex must be used */
							if (php_pgsql_convert_match(Z_STRVAL_PP(val), Z_STRLEN_PP(val), "^[0-9]+$", 0 TSRMLS_CC) == FAILURE) {
								err = 1;
							}
							else {
								ZVAL_STRING(new_val, Z_STRVAL_PP(val), 1);
								convert_to_long_ex(&new_val);
							}
						}
						break;

					case IS_DOUBLE:
						ZVAL_DOUBLE(new_val, Z_DVAL_PP(val));
						convert_to_long_ex(&new_val);
						break;

					case IS_LONG:
						ZVAL_LONG(new_val, Z_LVAL_PP(val));
						break;

					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL, string, long or double value for '%s' (%s)", Z_STRVAL_PP(type), field);
				}
				break;

			case PG_CIDR:
			case PG_INET:
				switch (Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {
							/* FIXME: Better regex must be used */
							if (php_pgsql_convert_match(Z_STRVAL_PP(val), Z_STRLEN_PP(val), "^([0-9]{1,3}\\.){3}[0-9]{1,3}(/[0-9]{1,2}){0,1}$", 0 TSRMLS_CC) == FAILURE) {
								err = 1;
							}
							else {
								ZVAL_STRING(new_val, Z_STRVAL_PP(val), 1);
								php_pgsql_add_quotes(new_val, 1 TSRMLS_CC);
							}
						}
						break;
						
					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL or string for '%s' (%s)", Z_STRVAL_PP(type), field);
				}
				break;

			case PG_TIME_WITH_TIMEZONE:
			case PG_TIMESTAMP:
			case PG_TIMESTAMP_WITH_TIMEZONE:
				switch(Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRINGL(new_val, "NULL", sizeof("NULL")-1, 1);
						} else if (!strcasecmp(Z_STRVAL_PP(val), "now()")) {
							ZVAL_STRINGL(new_val, "NOW()", sizeof("NOW()")-1, 1);
						} else {
							/* FIXME: better regex must be used */
							if (php_pgsql_convert_match(Z_STRVAL_PP(val), Z_STRLEN_PP(val), "^([0-9]{4}[/-][0-9]{1,2}[/-][0-9]{1,2})([ \\t]+(([0-9]{1,2}:[0-9]{1,2}){1}(:[0-9]{1,2}){0,1}(\\.[0-9]+){0,1}([ \\t]*([+-][0-9]{1,4}(:[0-9]{1,2}){0,1}|[-a-zA-Z_/+]{1,50})){0,1})){0,1}$", 1 TSRMLS_CC) == FAILURE) {
								err = 1;
							} else {
								ZVAL_STRING(new_val, Z_STRVAL_PP(val), 1);
								php_pgsql_add_quotes(new_val, 1 TSRMLS_CC);
							}
						}
						break;

					case IS_NULL:
						ZVAL_STRINGL(new_val, "NULL", sizeof("NULL")-1, 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL or string for PostgreSQL %s field (%s)", Z_STRVAL_PP(type), field);
				}
				break;

			case PG_DATE:
				switch(Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {
							/* FIXME: better regex must be used */
							if (php_pgsql_convert_match(Z_STRVAL_PP(val), Z_STRLEN_PP(val), "^([0-9]{4}[/-][0-9]{1,2}[/-][0-9]{1,2})$", 1 TSRMLS_CC) == FAILURE) {
								err = 1;
							}
							else {
								ZVAL_STRING(new_val, Z_STRVAL_PP(val), 1);
								php_pgsql_add_quotes(new_val, 1 TSRMLS_CC);
							}
						}
						break;

					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL or string for PostgreSQL %s field (%s)", Z_STRVAL_PP(type), field);
				}
				break;

			case PG_TIME:
				switch(Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {
							/* FIXME: better regex must be used */
							if (php_pgsql_convert_match(Z_STRVAL_PP(val), Z_STRLEN_PP(val), "^(([0-9]{1,2}:[0-9]{1,2}){1}(:[0-9]{1,2}){0,1})){0,1}$", 1 TSRMLS_CC) == FAILURE) {
								err = 1;
							}
							else {
								ZVAL_STRING(new_val, Z_STRVAL_PP(val), 1);
								php_pgsql_add_quotes(new_val, 1 TSRMLS_CC);
							}
						}
						break;

					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL or string for PostgreSQL %s field (%s)", Z_STRVAL_PP(type), field);
				}
				break;

			case PG_INTERVAL:
				switch(Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {

							/* From the Postgres docs:

							   interval values can be written with the following syntax:
							   [@] quantity unit [quantity unit...] [direction]
							   
							   Where: quantity is a number (possibly signed); unit is second, minute, hour,
							   day, week, month, year, decade, century, millennium, or abbreviations or
							   plurals of these units [note not *all* abbreviations] ; direction can be
							   ago or empty. The at sign (@) is optional noise.
							   
							   ...
							   
							   Quantities of days, hours, minutes, and seconds can be specified without explicit
							   unit markings. For example, '1 12:59:10' is read the same as '1 day 12 hours 59 min 10
							   sec'.
							*/
							if (php_pgsql_convert_match(Z_STRVAL_PP(val), Z_STRLEN_PP(val),
														"^(@?[ \\t]+)?("

														/* Textual time units and their abbreviations: */
														"(([-+]?[ \\t]+)?"
														"[0-9]+(\\.[0-9]*)?[ \\t]*"
														"(millenniums|millennia|millennium|mil|mils|"
														"centuries|century|cent|c|"
														"decades|decade|dec|decs|"
														"years|year|y|"
														"months|month|mon|"
														"weeks|week|w|" 
														"days|day|d|"
														"hours|hour|hr|hrs|h|"
														"minutes|minute|mins|min|m|"
														"seconds|second|secs|sec|s))+|"

														/* Textual time units plus (dd)* hh[:mm[:ss]] */
														"((([-+]?[ \\t]+)?"
														"[0-9]+(\\.[0-9]*)?[ \\t]*"
														"(millenniums|millennia|millennium|mil|mils|"
														"centuries|century|cent|c|"
														"decades|decade|dec|decs|"
														"years|year|y|"
														"months|month|mon|"
														"weeks|week|w|"
														"days|day|d))+" 
														"([-+]?[ \\t]+"
														"([0-9]+[ \\t]+)+"				 /* dd */
														"(([0-9]{1,2}:){0,2}[0-9]{0,2})" /* hh:[mm:[ss]] */
														")?))"
														"([ \\t]+ago)?$",
														1 TSRMLS_CC) == FAILURE) {
								err = 1;
							}
							else {
								ZVAL_STRING(new_val, Z_STRVAL_PP(val), 1);
								php_pgsql_add_quotes(new_val, 1 TSRMLS_CC);
							}
						}
						break;

					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL or string for PostgreSQL %s field (%s)", Z_STRVAL_PP(type), field);
				}
				break;
#ifdef HAVE_PQESCAPE
			case PG_BYTEA:
				switch (Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {
							unsigned char *tmp;
							size_t to_len;
							smart_str s = {0};
#ifdef HAVE_PQESCAPE_BYTEA_CONN
							tmp = PQescapeByteaConn(pg_link, (unsigned char *)Z_STRVAL_PP(val), Z_STRLEN_PP(val), &to_len);
#else
							tmp = PQescapeBytea(Z_STRVAL_PP(val), (unsigned char *)Z_STRLEN_PP(val), &to_len);
#endif
							Z_TYPE_P(new_val) = IS_STRING;
							Z_STRLEN_P(new_val) = to_len-1; /* PQescapeBytea's to_len includes additional '\0' */
							Z_STRVAL_P(new_val) = emalloc(to_len);
							memcpy(Z_STRVAL_P(new_val), tmp, to_len);
							PQfreemem(tmp);
							php_pgsql_add_quotes(new_val, 1 TSRMLS_CC);
							smart_str_appendl(&s, Z_STRVAL_P(new_val), Z_STRLEN_P(new_val));
							smart_str_0(&s);
							efree(Z_STRVAL_P(new_val));
							Z_STRVAL_P(new_val) = s.c;
							Z_STRLEN_P(new_val) = s.len;
						}
						break;

					case IS_LONG:
						ZVAL_LONG(new_val, Z_LVAL_PP(val));
						convert_to_string_ex(&new_val);
						break;

					case IS_DOUBLE:
						ZVAL_DOUBLE(new_val, Z_DVAL_PP(val));
						convert_to_string_ex(&new_val);
						break;

					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL, string, long or double value for PostgreSQL '%s' (%s)", Z_STRVAL_PP(type), field);
				}
				break;
				
#endif
			case PG_MACADDR:
				switch(Z_TYPE_PP(val)) {
					case IS_STRING:
						if (Z_STRLEN_PP(val) == 0) {
							ZVAL_STRING(new_val, "NULL", 1);
						}
						else {
							if (php_pgsql_convert_match(Z_STRVAL_PP(val), Z_STRLEN_PP(val), "^([0-9a-f]{2,2}:){5,5}[0-9a-f]{2,2}$", 1 TSRMLS_CC) == FAILURE) {
								err = 1;
							}
							else {
								ZVAL_STRING(new_val, Z_STRVAL_PP(val), 1);
								php_pgsql_add_quotes(new_val, 1 TSRMLS_CC);
							}
						}
						break;

					case IS_NULL:
						ZVAL_STRING(new_val, "NULL", 1);
						break;

					default:
						err = 1;
				}
				PGSQL_CONV_CHECK_IGNORE();
				if (err) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Expects NULL or string for PostgreSQL %s field (%s)", Z_STRVAL_PP(type), field);
				}
				break;

				/* bit */
			case PG_BIT:
			case PG_VARBIT:
				/* geometric */
			case PG_LINE:
			case PG_LSEG:
			case PG_POINT:
			case PG_BOX:
			case PG_PATH:
			case PG_POLYGON:
			case PG_CIRCLE:
				php_error_docref(NULL TSRMLS_CC, E_NOTICE, "PostgreSQL '%s' type (%s) is not supported", Z_STRVAL_PP(type), field);
				err = 1;
				break;
				
			case PG_UNKNOWN:
			default:
				php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Unknown or system data type '%s' for '%s'", Z_STRVAL_PP(type), field);
				err = 1;
				break;
		} /* switch */

		if (err) {
			zval_dtor(new_val);
			FREE_ZVAL(new_val);
			break; /* break out for() */
		}
		/* If field is NULL and HAS DEFAULT, should be skipped */
		if (!skip_field) {
			char *escaped;
			size_t field_len = strlen(field);

			if (_php_pgsql_detect_identifier_escape(field, field_len) == SUCCESS) {
				add_assoc_zval(result, field, new_val);
			} else {
				escaped = PGSQLescapeIdentifier(pg_link, field, field_len);
				add_assoc_zval(result, escaped, new_val);
				PGSQLfree(escaped);
			}
		}
	} /* for */
	zval_dtor(meta);
	FREE_ZVAL(meta);

	if (err) {
		/* shouldn't destroy & free zval here */
		return FAILURE;
	}
	return SUCCESS;
}
