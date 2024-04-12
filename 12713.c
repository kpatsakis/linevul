PHP_MINFO_FUNCTION(phar) /* {{{ */
{
	phar_request_initialize(TSRMLS_C);
	php_info_print_table_start();
	php_info_print_table_header(2, "Phar: PHP Archive support", "enabled");
	php_info_print_table_row(2, "Phar EXT version", PHP_PHAR_VERSION);
	php_info_print_table_row(2, "Phar API version", PHP_PHAR_API_VERSION);
	php_info_print_table_row(2, "SVN revision", "$Id$");
	php_info_print_table_row(2, "Phar-based phar archives", "enabled");
	php_info_print_table_row(2, "Tar-based phar archives", "enabled");
	php_info_print_table_row(2, "ZIP-based phar archives", "enabled");

	if (PHAR_G(has_zlib)) {
		php_info_print_table_row(2, "gzip compression", "enabled");
	} else {
		php_info_print_table_row(2, "gzip compression", "disabled (install ext/zlib)");
	}

	if (PHAR_G(has_bz2)) {
		php_info_print_table_row(2, "bzip2 compression", "enabled");
	} else {
		php_info_print_table_row(2, "bzip2 compression", "disabled (install pecl/bz2)");
	}
#ifdef PHAR_HAVE_OPENSSL
	php_info_print_table_row(2, "Native OpenSSL support", "enabled");
#else
	if (zend_hash_exists(&module_registry, "openssl", sizeof("openssl"))) {
		php_info_print_table_row(2, "OpenSSL support", "enabled");
	} else {
		php_info_print_table_row(2, "OpenSSL support", "disabled (install ext/openssl)");
	}
#endif
	php_info_print_table_end();

	php_info_print_box_start(0);
	PUTS("Phar based on pear/PHP_Archive, original concept by Davey Shafik.");
	PUTS(!sapi_module.phpinfo_as_text?"<br />":"\n");
	PUTS("Phar fully realized by Gregory Beaver and Marcus Boerger.");
	PUTS(!sapi_module.phpinfo_as_text?"<br />":"\n");
	PUTS("Portions of tar implementation Copyright (c) 2003-2009 Tim Kientzle.");
	php_info_print_box_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */
