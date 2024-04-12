connection_timeout(thread_t * thread)
{
	smtp_t *smtp = THREAD_ARG(thread);

	log_message(LOG_INFO, "Timeout connecting SMTP server %s."
			    , FMT_SMTP_HOST());
	free_smtp_all(smtp);
	return 0;
}
