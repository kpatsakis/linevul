GahpClient::clear_pending()
{
	if ( pending_reqid ) {
		if (server->requestTable->remove(pending_reqid) == 0) {
			server->requestTable->insert(pending_reqid,NULL);
		}
	}
	pending_reqid = 0;
	if (pending_result) delete pending_result;
	pending_result = NULL;
	free(pending_command);
	pending_command = NULL;
	if (pending_args) free(pending_args);
	pending_args = NULL;
	pending_timeout = 0;
	if (pending_submitted_to_gahp) {
		server->num_pending_requests--;
	}
	pending_submitted_to_gahp = false;
	if ( pending_timeout_tid != -1 ) {
		daemonCore->Cancel_Timer(pending_timeout_tid);
		pending_timeout_tid = -1;
	}
}
