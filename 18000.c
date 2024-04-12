static int _server_handle_ques(libgdbr_t *g, int (*cmd_cb) (void*, const char*, char*, size_t), void *core_ptr) {
	char message[64];
	if (send_ack (g) < 0) {
		return -1;
	}
	snprintf (message, sizeof (message) - 1, "T05thread:%x;", cmd_cb (core_ptr, "dptr", NULL, 0));
	return send_msg (g, message);
}
