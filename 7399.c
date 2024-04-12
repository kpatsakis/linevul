static int handle_headers_frame(h2o_http2_conn_t *conn, h2o_http2_frame_t *frame, const char **err_desc)
{
    h2o_http2_headers_payload_t payload;
    h2o_http2_stream_t *stream;
    int ret;

    /* decode */
    if ((ret = h2o_http2_decode_headers_payload(&payload, frame, err_desc)) != 0)
        return ret;
    if ((frame->stream_id & 1) == 0) {
        *err_desc = "invalid stream id in HEADERS frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }
    if (!(conn->pull_stream_ids.max_open < frame->stream_id)) {
        if ((stream = h2o_http2_conn_get_stream(conn, frame->stream_id)) != NULL &&
            stream->state == H2O_HTTP2_STREAM_STATE_RECV_BODY) {
            /* is a trailer */
            if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_STREAM) == 0) {
                *err_desc = "trailing HEADERS frame MUST have END_STREAM flag set";
                return H2O_HTTP2_ERROR_PROTOCOL;
            }
            stream->req.entity = h2o_iovec_init(stream->_req_body->bytes, stream->_req_body->size);
            if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_HEADERS) == 0)
                goto PREPARE_FOR_CONTINUATION;
            return handle_trailing_headers(conn, stream, payload.headers, payload.headers_len, err_desc);
        }
        *err_desc = "invalid stream id in HEADERS frame";
        return H2O_HTTP2_ERROR_STREAM_CLOSED;
    }
    if (frame->stream_id == payload.priority.dependency) {
        *err_desc = "stream cannot depend on itself";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    if (conn->state >= H2O_HTTP2_CONN_STATE_HALF_CLOSED)
        return 0;

    /* open or determine the stream and prepare */
    if ((stream = h2o_http2_conn_get_stream(conn, frame->stream_id)) != NULL) {
        if ((frame->flags & H2O_HTTP2_FRAME_FLAG_PRIORITY) != 0)
            set_priority(conn, stream, &payload.priority, 1);
    } else {
        stream = h2o_http2_stream_open(conn, frame->stream_id, NULL);
        set_priority(conn, stream, &payload.priority, 0);
    }
    h2o_http2_stream_prepare_for_request(conn, stream);

    /* setup container for request body if it is expected to arrive */
    if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_STREAM) == 0)
        h2o_buffer_init(&stream->_req_body, &h2o_socket_buffer_prototype);

    if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_HEADERS) != 0) {
        /* request is complete, handle it */
        return handle_incoming_request(conn, stream, payload.headers, payload.headers_len, err_desc);
    }

PREPARE_FOR_CONTINUATION:
    /* request is not complete, store in buffer */
    conn->_read_expect = expect_continuation_of_headers;
    h2o_buffer_init(&conn->_headers_unparsed, &h2o_socket_buffer_prototype);
    h2o_buffer_reserve(&conn->_headers_unparsed, payload.headers_len);
    memcpy(conn->_headers_unparsed->bytes, payload.headers, payload.headers_len);
    conn->_headers_unparsed->size = payload.headers_len;
    return 0;
}
