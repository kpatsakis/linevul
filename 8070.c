_PUBLIC_ size_t strlen_m_ext_term(const char *s, const charset_t src_charset,
				  const charset_t dst_charset)
{
	if (!s) {
		return 0;
	}
	return strlen_m_ext(s, src_charset, dst_charset) + 1;
}
