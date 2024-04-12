static inline void mk_request_init(struct session_request *request)
{
    request->status = MK_TRUE;
    request->method = MK_HTTP_METHOD_UNKNOWN;

    request->file_info.size = -1;

    request->bytes_to_send = -1;
    request->fd_file = -1;

    /* Response Headers */
    mk_header_response_reset(&request->headers);
}
