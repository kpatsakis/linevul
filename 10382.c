static int cmd_rap_run(void *data, const char *input) {
	RCore *core = (RCore *)data;
	return r_io_system (core->io, input);
}
