static void execute_or_enqueue_request(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    assert(stream->state < H2O_HTTP2_STREAM_STATE_REQ_PENDING);

    if (stream->_req_body != NULL && stream->_expected_content_length != SIZE_MAX &&
        stream->_req_body->size != stream->_expected_content_length) {
        send_stream_error(conn, stream->stream_id, H2O_HTTP2_ERROR_PROTOCOL);
        h2o_http2_stream_reset(conn, stream);
        return;
    }

    h2o_http2_stream_set_state(conn, stream, H2O_HTTP2_STREAM_STATE_REQ_PENDING);

    /* TODO schedule the pending reqs using the scheduler */
    h2o_linklist_insert(&conn->_pending_reqs, &stream->_refs.link);

    run_pending_requests(conn);
    update_idle_timeout(conn);
}
