static void close_connection_now(h2o_http2_conn_t *conn)
{
    h2o_http2_stream_t *stream;

    assert(!h2o_timeout_is_linked(&conn->_write.timeout_entry));

    kh_foreach_value(conn->streams, stream, { h2o_http2_stream_close(conn, stream); });
    assert(conn->num_streams.pull.open == 0);
    assert(conn->num_streams.pull.half_closed == 0);
    assert(conn->num_streams.pull.send_body == 0);
    assert(conn->num_streams.push.half_closed == 0);
    assert(conn->num_streams.push.send_body == 0);
    assert(conn->num_streams.priority.open == 0);
    kh_destroy(h2o_http2_stream_t, conn->streams);
    assert(conn->_http1_req_input == NULL);
    h2o_hpack_dispose_header_table(&conn->_input_header_table);
    h2o_hpack_dispose_header_table(&conn->_output_header_table);
    assert(h2o_linklist_is_empty(&conn->_pending_reqs));
    h2o_timeout_unlink(&conn->_timeout_entry);
    h2o_buffer_dispose(&conn->_write.buf);
    if (conn->_write.buf_in_flight != NULL)
        h2o_buffer_dispose(&conn->_write.buf_in_flight);
    h2o_http2_scheduler_dispose(&conn->scheduler);
    assert(h2o_linklist_is_empty(&conn->_write.streams_to_proceed));
    assert(!h2o_timeout_is_linked(&conn->_write.timeout_entry));
    if (conn->_headers_unparsed != NULL)
        h2o_buffer_dispose(&conn->_headers_unparsed);
    if (conn->casper != NULL)
        h2o_http2_casper_destroy(conn->casper);
    h2o_linklist_unlink(&conn->_conns);

    if (conn->sock != NULL)
        h2o_socket_close(conn->sock);
     free(conn);
 }
