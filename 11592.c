static void request_gathered_write(h2o_http2_conn_t *conn)
{
    assert(conn->state < H2O_HTTP2_CONN_STATE_IS_CLOSING);
    if (conn->_write.buf_in_flight == NULL) {
        if (!h2o_timeout_is_linked(&conn->_write.timeout_entry))
            h2o_timeout_link(conn->super.ctx->loop, &conn->super.ctx->zero_timeout, &conn->_write.timeout_entry);
    }
}
