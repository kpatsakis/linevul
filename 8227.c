static TEE_Result copy_in_attrs(struct user_ta_ctx *utc,
			const struct utee_attribute *usr_attrs,
			uint32_t attr_count, TEE_Attribute *attrs)
{
	TEE_Result res;
	uint32_t n;

	res = tee_mmu_check_access_rights(utc,
			TEE_MEMORY_ACCESS_READ | TEE_MEMORY_ACCESS_ANY_OWNER,
			(uaddr_t)usr_attrs,
			attr_count * sizeof(struct utee_attribute));
	if (res != TEE_SUCCESS)
		return res;

	for (n = 0; n < attr_count; n++) {
		attrs[n].attributeID = usr_attrs[n].attribute_id;
		if (attrs[n].attributeID & TEE_ATTR_BIT_VALUE) {
			attrs[n].content.value.a = usr_attrs[n].a;
			attrs[n].content.value.b = usr_attrs[n].b;
		} else {
			uintptr_t buf = usr_attrs[n].a;
			size_t len = usr_attrs[n].b;

			res = tee_mmu_check_access_rights(utc,
				TEE_MEMORY_ACCESS_READ |
				TEE_MEMORY_ACCESS_ANY_OWNER, buf, len);
			if (res != TEE_SUCCESS)
				return res;
			attrs[n].content.ref.buffer = (void *)buf;
			attrs[n].content.ref.length = len;
		}
	}

	return TEE_SUCCESS;
}
