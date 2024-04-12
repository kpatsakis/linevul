ssh_packet_read_poll_seqnr(struct ssh *ssh, u_char *typep, u_int32_t *seqnr_p)
{
	struct session_state *state = ssh->state;
	u_int reason, seqnr;
	int r;
	u_char *msg;

	for (;;) {
		msg = NULL;
		if (compat20) {
			r = ssh_packet_read_poll2(ssh, typep, seqnr_p);
			if (r != 0)
				return r;
			if (*typep) {
				state->keep_alive_timeouts = 0;
				DBG(debug("received packet type %d", *typep));
			}
			switch (*typep) {
			case SSH2_MSG_IGNORE:
				debug3("Received SSH2_MSG_IGNORE");
				break;
			case SSH2_MSG_DEBUG:
				if ((r = sshpkt_get_u8(ssh, NULL)) != 0 ||
				    (r = sshpkt_get_string(ssh, &msg, NULL)) != 0 ||
				    (r = sshpkt_get_string(ssh, NULL, NULL)) != 0) {
					free(msg);
					return r;
				}
				debug("Remote: %.900s", msg);
				free(msg);
				break;
			case SSH2_MSG_DISCONNECT:
				if ((r = sshpkt_get_u32(ssh, &reason)) != 0 ||
				    (r = sshpkt_get_string(ssh, &msg, NULL)) != 0)
					return r;
				/* Ignore normal client exit notifications */
				do_log2(ssh->state->server_side &&
				    reason == SSH2_DISCONNECT_BY_APPLICATION ?
				    SYSLOG_LEVEL_INFO : SYSLOG_LEVEL_ERROR,
				    "Received disconnect from %s port %d:"
				    "%u: %.400s", ssh_remote_ipaddr(ssh),
				    ssh_remote_port(ssh), reason, msg);
				free(msg);
				return SSH_ERR_DISCONNECTED;
			case SSH2_MSG_UNIMPLEMENTED:
				if ((r = sshpkt_get_u32(ssh, &seqnr)) != 0)
					return r;
				debug("Received SSH2_MSG_UNIMPLEMENTED for %u",
				    seqnr);
				break;
			default:
				return 0;
			}
		} else {
			r = ssh_packet_read_poll1(ssh, typep);
			switch (*typep) {
			case SSH_MSG_NONE:
				return SSH_MSG_NONE;
			case SSH_MSG_IGNORE:
				break;
			case SSH_MSG_DEBUG:
				if ((r = sshpkt_get_string(ssh, &msg, NULL)) != 0)
					return r;
				debug("Remote: %.900s", msg);
				free(msg);
				break;
			case SSH_MSG_DISCONNECT:
				if ((r = sshpkt_get_string(ssh, &msg, NULL)) != 0)
					return r;
				error("Received disconnect from %s port %d: "
				    "%.400s", ssh_remote_ipaddr(ssh),
				    ssh_remote_port(ssh), msg);
				free(msg);
				return SSH_ERR_DISCONNECTED;
			default:
				DBG(debug("received packet type %d", *typep));
				return 0;
			}
		}
	}
}
