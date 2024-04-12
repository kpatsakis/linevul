UNCURL_EXPORT void uncurl_free_tls_ctx(struct uncurl_tls_ctx *uc_tls)
{
	if (!uc_tls) return;

	tlss_free(uc_tls->tlss);

	free(uc_tls);
}
