static PHP_MSHUTDOWN_FUNCTION(zip)
{
	zend_hash_destroy(&zip_prop_handlers);
	php_unregister_url_stream_wrapper("zip");
	return SUCCESS;
}
