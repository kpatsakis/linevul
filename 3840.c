PHP_PGSQL_API int php_pgsql_meta_data(PGconn *pg_link, const char *table_name, zval *meta TSRMLS_DC) 
{
	PGresult *pg_result;
	char *src, *tmp_name, *tmp_name2 = NULL;
	char *escaped;
	smart_str querystr = {0};
	size_t new_len;
	int i, num_rows;
	zval *elem;

	if (!*table_name) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "The table name must be specified");
		return FAILURE;
	}

	src = estrdup(table_name);
	tmp_name = php_strtok_r(src, ".", &tmp_name2);
	
	if (!tmp_name2 || !*tmp_name2) {
		/* Default schema */
		tmp_name2 = tmp_name;
		tmp_name = "public";
	}

	smart_str_appends(&querystr, 
			"SELECT a.attname, a.attnum, t.typname, a.attlen, a.attnotnull, a.atthasdef, a.attndims, t.typtype = 'e' "
			"FROM pg_class as c, pg_attribute a, pg_type t, pg_namespace n "
			"WHERE a.attnum > 0 AND a.attrelid = c.oid AND c.relname = '");
	escaped = (char *)safe_emalloc(strlen(tmp_name2), 2, 1);
	new_len = PQescapeStringConn(pg_link, escaped, tmp_name2, strlen(tmp_name2), NULL);
	if (new_len) {
		smart_str_appendl(&querystr, escaped, new_len);
	}
	efree(escaped);

	smart_str_appends(&querystr, "' AND c.relnamespace = n.oid AND n.nspname = '");
	escaped = (char *)safe_emalloc(strlen(tmp_name), 2, 1);
	new_len = PQescapeStringConn(pg_link, escaped, tmp_name, strlen(tmp_name), NULL);
	if (new_len) {
		smart_str_appendl(&querystr, escaped, new_len);
	}
	efree(escaped);

	smart_str_appends(&querystr, "' AND a.atttypid = t.oid ORDER BY a.attnum;");
	smart_str_0(&querystr);
	efree(src);

	pg_result = PQexec(pg_link, querystr.c);
	if (PQresultStatus(pg_result) != PGRES_TUPLES_OK || (num_rows = PQntuples(pg_result)) == 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Table '%s' doesn't exists", table_name);
		smart_str_free(&querystr);
		PQclear(pg_result);
		return FAILURE;
	}
	smart_str_free(&querystr);

	for (i = 0; i < num_rows; i++) {
		char *name;
		MAKE_STD_ZVAL(elem);
		array_init(elem);
		add_assoc_long(elem, "num", atoi(PQgetvalue(pg_result,i,1)));
		add_assoc_string(elem, "type", PQgetvalue(pg_result,i,2), 1);
		add_assoc_long(elem, "len", atoi(PQgetvalue(pg_result,i,3)));
		if (!strcmp(PQgetvalue(pg_result,i,4), "t")) {
			add_assoc_bool(elem, "not null", 1);
		}
		else {
			add_assoc_bool(elem, "not null", 0);
		}
		if (!strcmp(PQgetvalue(pg_result,i,5), "t")) {
			add_assoc_bool(elem, "has default", 1);
		}
		else {
			add_assoc_bool(elem, "has default", 0);
		}
		add_assoc_long(elem, "array dims", atoi(PQgetvalue(pg_result,i,6)));
		if (!strcmp(PQgetvalue(pg_result,i,7), "t")) {
			add_assoc_bool(elem, "is enum", 1);
		}
		else {
			add_assoc_bool(elem, "is enum", 0);
		}
		name = PQgetvalue(pg_result,i,0);
		add_assoc_zval(meta, name, elem);
	}
	PQclear(pg_result);
	
	return SUCCESS;
}
