struct nls_table *load_nls(char *charset)
{
	return try_then_request_module(find_nls(charset), "nls_%s", charset);
}
