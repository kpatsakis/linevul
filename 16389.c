ZEND_API void zend_ts_hash_copy_to_hash(HashTable *target, TsHashTable *source, copy_ctor_func_t pCopyConstructor)
{
	begin_read(source);
	zend_hash_copy(target, TS_HASH(source), pCopyConstructor);
	end_read(source);
}
