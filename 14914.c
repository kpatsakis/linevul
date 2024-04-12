void lxc_delete_tty(struct lxc_tty_info *tty_info)
{
	int i;

	for (i = 0; i < tty_info->nbtty; i++) {
		struct lxc_pty_info *pty_info = &tty_info->pty_info[i];

		close(pty_info->master);
		close(pty_info->slave);
	}

	free(tty_info->pty_info);
	tty_info->nbtty = 0;
}
