void r_pkcs7_free_attributes (RPKCS7Attributes* attributes) {
	ut32 i;
	if (attributes) {
		for (i = 0; i < attributes->length; ++i) {
			r_pkcs7_free_attribute (attributes->elements[i]);
		}
		R_FREE (attributes->elements);
	}
}