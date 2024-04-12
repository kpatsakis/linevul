get_response(struct mg_connection *conn, char *ebuf, size_t ebuf_len, int *err)
{
	const char *cl;
	if (!get_message(conn, ebuf, ebuf_len, err)) {
		return 0;
	}

	if (parse_http_response(conn->buf, conn->buf_size, &conn->response_info)
	    <= 0) {
		mg_snprintf(conn,
		            NULL, /* No truncation check for ebuf */
		            ebuf,
		            ebuf_len,
		            "%s",
		            "Bad response");
		*err = 400;
		return 0;
	}

	/* Message is a valid response */

	/* Do we know the content length? */
	if ((cl = get_header(conn->response_info.http_headers,
	                     conn->response_info.num_headers,
	                     "Content-Length")) != NULL) {
		/* Request/response has content length set */
		char *endptr = NULL;
		conn->content_len = strtoll(cl, &endptr, 10);
		if (endptr == cl) {
			mg_snprintf(conn,
			            NULL, /* No truncation check for ebuf */
			            ebuf,
			            ebuf_len,
			            "%s",
			            "Bad request");
			*err = 411;
			return 0;
		}
		/* Publish the content length back to the response info. */
		conn->response_info.content_length = conn->content_len;

		/* TODO: check if it is still used in response_info */
		conn->request_info.content_length = conn->content_len;

	} else if ((cl = get_header(conn->response_info.http_headers,
	                            conn->response_info.num_headers,
	                            "Transfer-Encoding")) != NULL
	           && !mg_strcasecmp(cl, "chunked")) {
		conn->is_chunked = 1;
		conn->content_len = -1; /* unknown content length */
	} else {
		conn->content_len = -1; /* unknown content length */
	}

	conn->connection_type = CONNECTION_TYPE_RESPONSE; /* Valid response */
	return 1;
}
