ZEND_API ZEND_FUNCTION(display_disabled_function)
{
	zend_error(E_WARNING, "%s() has been disabled for security reasons", get_active_function_name(TSRMLS_C));
}
