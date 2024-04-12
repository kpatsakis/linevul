ssh_packet_not_very_much_data_to_write(struct ssh *ssh)
{
	if (ssh->state->interactive_mode)
		return sshbuf_len(ssh->state->output) < 16384;
	else
		return sshbuf_len(ssh->state->output) < 128 * 1024;
}
