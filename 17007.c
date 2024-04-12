get_http_method_info(const char *method)
{
	/* Check if the method is known to the server. The list of all known
	 * HTTP methods can be found here at
	 * http://www.iana.org/assignments/http-methods/http-methods.xhtml
	 */
	const struct mg_http_method_info *m = http_methods;

	while (m->name) {
		if (!strcmp(m->name, method)) {
			return m;
		}
		m++;
	}
	return NULL;
}
