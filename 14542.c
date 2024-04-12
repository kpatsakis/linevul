static PHP_RSHUTDOWN_FUNCTION(zlib)
{
	php_zlib_cleanup_ob_gzhandler_mess(TSRMLS_C);
    ZLIBG(handler_registered) = 0;

    return SUCCESS;
}
