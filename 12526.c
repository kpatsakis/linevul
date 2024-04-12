notify_fifo_script(vector_t *strvec, const char *type, notify_fifo_t *fifo)
{
	char *id_str;

	if (vector_size(strvec) < 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "No %snotify_fifo_script specified", type);
		return;
	}

	if (fifo->script) {
		report_config_error(CONFIG_GENERAL_ERROR, "%snotify_fifo_script already specified - ignoring %s", type, FMT_STR_VSLOT(strvec,1));
		return;
	}

	id_str = MALLOC(strlen(type) + strlen("notify_fifo") + 1);
	strcpy(id_str, type);
	strcat(id_str, "notify_fifo");
	fifo->script = notify_script_init(1, id_str);

	FREE(id_str);
}
