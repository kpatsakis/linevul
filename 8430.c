mux_tty_alloc_failed(Channel *c)
{
	Buffer m;
	Channel *mux_chan;

	debug3("%s: channel %d: TTY alloc failed", __func__, c->self);

	if ((mux_chan = channel_by_id(c->ctl_chan)) == NULL)
		fatal("%s: channel %d missing mux channel %d",
		    __func__, c->self, c->ctl_chan);

	/* Append exit message packet to control socket output queue */
	buffer_init(&m);
	buffer_put_int(&m, MUX_S_TTY_ALLOC_FAIL);
	buffer_put_int(&m, c->self);

	buffer_put_string(&mux_chan->output, buffer_ptr(&m), buffer_len(&m));
	buffer_free(&m);
}
