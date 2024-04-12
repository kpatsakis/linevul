ZEND_API void zend_object_proxy_set(zval **property, zval *value TSRMLS_DC)
{
	zend_proxy_object *probj = zend_object_store_get_object(*property TSRMLS_CC);

	if (Z_OBJ_HT_P(probj->object) && Z_OBJ_HT_P(probj->object)->write_property) {
		Z_OBJ_HT_P(probj->object)->write_property(probj->object, probj->property, value, 0 TSRMLS_CC);
	} else {
		zend_error(E_WARNING, "Cannot write property of object - no write handler defined");
	}
}
