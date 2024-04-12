static void airo_set_promisc(struct airo_info *ai) {
	Cmd cmd;
	Resp rsp;

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd=CMD_SETMODE;
	clear_bit(JOB_PROMISC, &ai->jobs);
	cmd.parm0=(ai->flags&IFF_PROMISC) ? PROMISC : NOPROMISC;
	issuecommand(ai, &cmd, &rsp);
	up(&ai->sem);
}
