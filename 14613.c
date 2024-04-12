static void php_pgsql_get_link_info(INTERNAL_FUNCTION_PARAMETERS, int entry_type)
{
	zval *pgsql_link = NULL;
	int id = -1, argc = ZEND_NUM_ARGS();
	PGconn *pgsql;
	char *msgbuf;

	if (zend_parse_parameters(argc TSRMLS_CC, "|r", &pgsql_link) == FAILURE) {
		return;
	}
	
	if (argc == 0) {
		id = PGG(default_link);
		CHECK_DEFAULT_LINK(id);
	}
	
	if (pgsql_link == NULL && id == -1) {
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE2(pgsql, PGconn *, &pgsql_link, id, "PostgreSQL link", le_link, le_plink);

	switch(entry_type) {
		case PHP_PG_DBNAME:
			Z_STRVAL_P(return_value) = PQdb(pgsql);
			break;
		case PHP_PG_ERROR_MESSAGE:
			RETURN_STRING(PQErrorMessageTrim(pgsql, &msgbuf), 0);
			return;
		case PHP_PG_OPTIONS:
			Z_STRVAL_P(return_value) = PQoptions(pgsql);
			break;
		case PHP_PG_PORT:
			Z_STRVAL_P(return_value) = PQport(pgsql);
			break;
		case PHP_PG_TTY:
			Z_STRVAL_P(return_value) = PQtty(pgsql);
			break;
		case PHP_PG_HOST:
			Z_STRVAL_P(return_value) = PQhost(pgsql);
			break;
		case PHP_PG_VERSION:
			array_init(return_value);
			add_assoc_string(return_value, "client", PG_VERSION, 1);
#if HAVE_PQPROTOCOLVERSION
			add_assoc_long(return_value, "protocol", PQprotocolVersion(pgsql));
#if HAVE_PQPARAMETERSTATUS
			if (PQprotocolVersion(pgsql) >= 3) {
				add_assoc_string(return_value, "server", (char*)PQparameterStatus(pgsql, "server_version"), 1);
			}
#endif
#endif
			return;
		default:
			RETURN_FALSE;
	}
	if (Z_STRVAL_P(return_value)) {
		Z_STRLEN_P(return_value) = strlen(Z_STRVAL_P(return_value));
		Z_STRVAL_P(return_value) = (char *) estrdup(Z_STRVAL_P(return_value));
	} else {
		Z_STRLEN_P(return_value) = 0;
		Z_STRVAL_P(return_value) = (char *) estrdup("");
	}
	Z_TYPE_P(return_value) = IS_STRING;
}
