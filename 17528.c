static int http_buf_read_compressed(URLContext *h, uint8_t *buf, int size)
{
    HTTPContext *s = h->priv_data;
    int ret;

    if (!s->inflate_buffer) {
        s->inflate_buffer = av_malloc(DECOMPRESS_BUF_SIZE);
        if (!s->inflate_buffer)
            return AVERROR(ENOMEM);
    }

    if (s->inflate_stream.avail_in == 0) {
        int read = http_buf_read(h, s->inflate_buffer, DECOMPRESS_BUF_SIZE);
        if (read <= 0)
            return read;
        s->inflate_stream.next_in  = s->inflate_buffer;
        s->inflate_stream.avail_in = read;
    }

    s->inflate_stream.avail_out = size;
    s->inflate_stream.next_out  = buf;

    ret = inflate(&s->inflate_stream, Z_SYNC_FLUSH);
    if (ret != Z_OK && ret != Z_STREAM_END)
        av_log(h, AV_LOG_WARNING, "inflate return value: %d, %s\n",
               ret, s->inflate_stream.msg);

    return size - s->inflate_stream.avail_out;
}
