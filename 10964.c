static int is_idle_stream_id(h2o_http2_conn_t *conn, uint32_t stream_id)
{
    return (h2o_http2_stream_is_push(stream_id) ? conn->push_stream_ids.max_open : conn->pull_stream_ids.max_open) < stream_id;
}
