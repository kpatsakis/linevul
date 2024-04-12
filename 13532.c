static int _server_handle_Hg(libgdbr_t *g, int (*cmd_cb) (void*, const char*, char*, size_t), void *core_ptr) {
	char cmd[32];
	int tid;
	if (send_ack (g) < 0) {
		return -1;
	}
	if (g->data_len <= 2 || isalpha (g->data[2])) {
		return send_msg (g, "E01");
	}
	if (g->data[2] == '0' || !strncmp (g->data + 2, "-1", 2)) {
		return send_msg (g, "OK");
	}
	sscanf (g->data + 2, "%x", &tid);
	snprintf (cmd, sizeof (cmd) - 1, "dpt=%d", tid);
	if (cmd_cb (core_ptr, cmd, NULL, 0) < 0) {
		send_msg (g, "E01");
		return -1;
	}
	return send_msg (g, "OK");
}
