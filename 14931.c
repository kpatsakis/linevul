static void stroke_memusage(private_stroke_socket_t *this,
							stroke_msg_t *msg, FILE *out)
{
	if (lib->leak_detective)
	{
		lib->leak_detective->usage(lib->leak_detective,
								   (leak_detective_report_cb_t)report_usage,
								   (leak_detective_summary_cb_t)sum_usage, out);
	}
}
