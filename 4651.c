static void php_zlib_cleanup_ob_gzhandler_mess(TSRMLS_D)
{
	if (ZLIBG(ob_gzhandler)) {
		deflateEnd(&(ZLIBG(ob_gzhandler)->Z));
		php_zlib_output_handler_context_dtor(ZLIBG(ob_gzhandler) TSRMLS_CC);
		ZLIBG(ob_gzhandler) = NULL;
	}
}
