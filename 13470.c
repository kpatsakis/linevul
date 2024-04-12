xmlBufEmpty(xmlBufPtr buf) {
    if ((buf == NULL) || (buf->error != 0)) return;
    if (buf->content == NULL) return;
    CHECK_COMPAT(buf)
    buf->use = 0;
    if (buf->alloc == XML_BUFFER_ALLOC_IMMUTABLE) {
        buf->content = BAD_CAST "";
    } else if ((buf->alloc == XML_BUFFER_ALLOC_IO) &&
               (buf->contentIO != NULL)) {
        size_t start_buf = buf->content - buf->contentIO;

	buf->size += start_buf;
        buf->content = buf->contentIO;
        buf->content[0] = 0;
    } else {
        buf->content[0] = 0;
    }
    UPDATE_COMPAT(buf)
}
