static const wbxml_decoding *get_wbxml_decoding_from_content_type (
								   const char *content_type, tvbuff_t *tvb, guint32 offset)
{
	const wbxml_decoding *map = NULL;

	DebugLog(("get_wbxml_decoding_from_content_type: content_type = [%s]\n",
		  content_type));
	if (content_type && content_type[0]) {
		const wbxml_literal_list *item = content_type_list;

		while (item && item->content_type) {
			if (g_ascii_strcasecmp(content_type, item->content_type) == 0) {
				/* Try the discriminator */
				if (item->discriminator != NULL) {
					map = item->discriminator(tvb, offset);
				}
				if (map == NULL) {
					map = item->map;
				}
				break;
			}
			item++;
		}
	}
	return map;
}
