get_message(struct mg_connection *conn, char *ebuf, size_t ebuf_len, int *err)
{
	if (ebuf_len > 0) {
		ebuf[0] = '\0';
	}
	*err = 0;

	reset_per_request_attributes(conn);

	if (!conn) {
		mg_snprintf(conn,
		            NULL, /* No truncation check for ebuf */
		            ebuf,
		            ebuf_len,
		            "%s",
		            "Internal error");
		*err = 500;
		return 0;
	}
	/* Set the time the request was received. This value should be used for
	 * timeouts. */
	clock_gettime(CLOCK_MONOTONIC, &(conn->req_time));

	conn->request_len =
	    read_message(NULL, conn, conn->buf, conn->buf_size, &conn->data_len);
	DEBUG_ASSERT(conn->request_len < 0 || conn->data_len >= conn->request_len);
	if ((conn->request_len >= 0) && (conn->data_len < conn->request_len)) {
		mg_snprintf(conn,
		            NULL, /* No truncation check for ebuf */
		            ebuf,
		            ebuf_len,
		            "%s",
		            "Invalid message size");
		*err = 500;
		return 0;
	}

	if ((conn->request_len == 0) && (conn->data_len == conn->buf_size)) {
		mg_snprintf(conn,
		            NULL, /* No truncation check for ebuf */
		            ebuf,
		            ebuf_len,
		            "%s",
		            "Message too large");
		*err = 413;
		return 0;
	}

	if (conn->request_len <= 0) {
		if (conn->data_len > 0) {
			mg_snprintf(conn,
			            NULL, /* No truncation check for ebuf */
			            ebuf,
			            ebuf_len,
			            "%s",
			            "Malformed message");
			*err = 400;
		} else {
			/* Server did not recv anything -> just close the connection */
			conn->must_close = 1;
			mg_snprintf(conn,
			            NULL, /* No truncation check for ebuf */
			            ebuf,
			            ebuf_len,
			            "%s",
			            "No data received");
			*err = 0;
		}
		return 0;
	}
	return 1;
}
