static int php_zip_has_property(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
	ze_zip_object *obj;
	zval tmp_member;
	zip_prop_handler *hnd = NULL;
	zend_object_handlers *std_hnd;
	int retval = 0;

	if (Z_TYPE_P(member) != IS_STRING) {
		ZVAL_COPY(&tmp_member, member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
		cache_slot = NULL;
	}

	obj = Z_ZIP_P(object);

	if (obj->prop_handler != NULL) {
		hnd = zend_hash_find_ptr(obj->prop_handler, Z_STR_P(member));
	}

	if (hnd != NULL) {
		zval tmp, *prop;

		if (type == 2) {
			retval = 1;
		} else if ((prop = php_zip_property_reader(obj, hnd, &tmp)) != NULL) {
			if (type == 1) {
				retval = zend_is_true(&tmp);
			} else if (type == 0) {
				retval = (Z_TYPE(tmp) != IS_NULL);
			}
		}

		zval_ptr_dtor(&tmp);
	} else {
		std_hnd = zend_get_std_object_handlers();
		retval = std_hnd->has_property(object, member, type, cache_slot);
	}

	if (member == &tmp_member) {
		zval_dtor(member);
	}

	return retval;
}
/* }}} */
