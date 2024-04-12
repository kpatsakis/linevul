static void xmlwriter_free_resource_ptr(xmlwriter_object *intern TSRMLS_DC) 
{
	if (intern) {
		if (intern->ptr) {
			xmlFreeTextWriter(intern->ptr);
			intern->ptr = NULL;
		}
		if (intern->output) {
			xmlBufferFree(intern->output);
			intern->output = NULL;
		}
		efree(intern);
	}
}
