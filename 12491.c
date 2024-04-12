ssh_packet_set_rekey_limits(struct ssh *ssh, u_int32_t bytes, time_t seconds)
{
	debug3("rekey after %lld bytes, %d seconds", (long long)bytes,
	    (int)seconds);
	ssh->state->rekey_limit = bytes;
	ssh->state->rekey_interval = seconds;
}
