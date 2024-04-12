server_init_dispatch(void)
{
	debug("server_init_dispatch");
	dispatch_init(&dispatch_protocol_error);
	dispatch_set(SSH2_MSG_CHANNEL_CLOSE, &channel_input_oclose);
	dispatch_set(SSH2_MSG_CHANNEL_DATA, &channel_input_data);
	dispatch_set(SSH2_MSG_CHANNEL_EOF, &channel_input_ieof);
	dispatch_set(SSH2_MSG_CHANNEL_EXTENDED_DATA, &channel_input_extended_data);
	dispatch_set(SSH2_MSG_CHANNEL_OPEN, &server_input_channel_open);
	dispatch_set(SSH2_MSG_CHANNEL_OPEN_CONFIRMATION, &channel_input_open_confirmation);
	dispatch_set(SSH2_MSG_CHANNEL_OPEN_FAILURE, &channel_input_open_failure);
	dispatch_set(SSH2_MSG_CHANNEL_REQUEST, &server_input_channel_req);
	dispatch_set(SSH2_MSG_CHANNEL_WINDOW_ADJUST, &channel_input_window_adjust);
	dispatch_set(SSH2_MSG_GLOBAL_REQUEST, &server_input_global_request);
	/* client_alive */
	dispatch_set(SSH2_MSG_CHANNEL_SUCCESS, &server_input_keep_alive);
	dispatch_set(SSH2_MSG_CHANNEL_FAILURE, &server_input_keep_alive);
	dispatch_set(SSH2_MSG_REQUEST_SUCCESS, &server_input_keep_alive);
	dispatch_set(SSH2_MSG_REQUEST_FAILURE, &server_input_keep_alive);
	/* rekeying */
	dispatch_set(SSH2_MSG_KEXINIT, &kex_input_kexinit);
}
