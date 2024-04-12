static int _server_handle_qTStatus(libgdbr_t *g) {
	int ret;
	const char *message = "";
	if ((ret = send_ack (g)) < 0) {
		return -1;
	}
	return send_msg (g, message);
}
