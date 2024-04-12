apr_status_t h2_stream_close_input(h2_stream *stream)
{
    conn_rec *c = stream->session->c;
    apr_status_t status;
    apr_bucket_brigade *tmp;
    apr_bucket *b;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                  "h2_stream(%ld-%d): closing input",
                  stream->session->id, stream->id);
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    
    tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
    if (stream->trailers && !apr_is_empty_table(stream->trailers)) {
        h2_headers *r = h2_headers_create(HTTP_OK, stream->trailers, 
                                          NULL, stream->pool);
        b = h2_bucket_headers_create(c->bucket_alloc, r);
        APR_BRIGADE_INSERT_TAIL(tmp, b);
        stream->trailers = NULL;
    }
    
    b = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(tmp, b);
    status = h2_beam_send(stream->input, tmp, APR_BLOCK_READ);
    apr_brigade_destroy(tmp);
    return status;
}
