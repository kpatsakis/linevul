static void pharobj_set_compression(HashTable *manifest, php_uint32 compress) /* {{{ */
{
	zend_hash_apply_with_argument(manifest, phar_set_compression, &compress);
}
/* }}} */
