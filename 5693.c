smtp_read_thread(thread_t * thread)
{
	smtp_t *smtp;
	char *buffer;
	char *reply;
	ssize_t rcv_buffer_size;
	int status = -1;

	smtp = THREAD_ARG(thread);

	if (thread->type == THREAD_READ_TIMEOUT) {
		log_message(LOG_INFO, "Timeout reading data to remote SMTP server %s."
				    , FMT_SMTP_HOST());
		SMTP_FSM_READ(QUIT, thread, 0);
		return -1;
	}

	buffer = smtp->buffer;

	rcv_buffer_size = read(thread->u.fd, buffer + smtp->buflen,
			       SMTP_BUFFER_LENGTH - smtp->buflen);

	if (rcv_buffer_size == -1) {
		if (errno == EAGAIN)
			goto end;
		log_message(LOG_INFO, "Error reading data from remote SMTP server %s."
				    , FMT_SMTP_HOST());
		SMTP_FSM_READ(QUIT, thread, 0);
		return 0;
	} else if (rcv_buffer_size == 0) {
		log_message(LOG_INFO, "Remote SMTP server %s has closed the connection."
				    , FMT_SMTP_HOST());
		SMTP_FSM_READ(QUIT, thread, 0);
		return 0;
	}

	/* received data overflow buffer size ? */
	if (smtp->buflen >= SMTP_BUFFER_MAX) {
		log_message(LOG_INFO, "Received buffer from remote SMTP server %s"
				      " overflow our get read buffer length."
				    , FMT_SMTP_HOST());
		SMTP_FSM_READ(QUIT, thread, 0);
		return 0;
	} else {
		smtp->buflen += (size_t)rcv_buffer_size;
		buffer[smtp->buflen] = 0;	/* NULL terminate */
	}

      end:

	/* parse the buffer, finding the last line of the response for the code */
	reply = buffer;
	while (reply < buffer + smtp->buflen) {
		char *p;

		p = strstr(reply, "\r\n");
		if (!p) {
			memmove(buffer, reply,
				smtp->buflen - (size_t)(reply - buffer));
			smtp->buflen -= (size_t)(reply - buffer);
			buffer[smtp->buflen] = 0;

			thread_add_read(thread->master, smtp_read_thread,
					smtp, thread->u.fd,
					global_data->smtp_connection_to);
			return 0;
		}

		if (reply[3] == '-') {
			/* Skip over the \r\n */
			reply = p + 2;
			continue;
		}

		status = ((reply[0] - '0') * 100) + ((reply[1] - '0') * 10) + (reply[2] - '0');

		reply = p + 2;
		break;
	}

	memmove(buffer, reply, smtp->buflen - (size_t)(reply - buffer));
	smtp->buflen -= (size_t)(reply - buffer);
	buffer[smtp->buflen] = 0;

	if (status == -1) {
		thread_add_read(thread->master, smtp_read_thread, smtp,
				thread->u.fd, global_data->smtp_connection_to);
		return 0;
	}

	SMTP_FSM_READ(smtp->stage, thread, status);

	/* Registering next smtp command processing thread */
	if (smtp->stage != ERROR) {
		thread_add_write(thread->master, smtp_send_thread, smtp,
				 smtp->fd, global_data->smtp_connection_to);
	} else {
		log_message(LOG_INFO, "Can not read data from remote SMTP server %s."
				    , FMT_SMTP_HOST());
		SMTP_FSM_READ(QUIT, thread, 0);
	}

	return 0;
}
