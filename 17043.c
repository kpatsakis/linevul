 static inline void php_rinit_session_globals(TSRMLS_D) /* {{{ */
 {
	PS(mod_data) = NULL;
	PS(mod_user_is_open) = 0;
	/* Do NOT init PS(mod_user_names) here! */
	PS(http_session_vars) = NULL;
}
/* }}} */
