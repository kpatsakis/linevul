static u16 issuecommand(struct airo_info *ai, Cmd *pCmd, Resp *pRsp) {
	int max_tries = 600000;

	if (IN4500(ai, EVSTAT) & EV_CMD)
		OUT4500(ai, EVACK, EV_CMD);

	OUT4500(ai, PARAM0, pCmd->parm0);
	OUT4500(ai, PARAM1, pCmd->parm1);
	OUT4500(ai, PARAM2, pCmd->parm2);
	OUT4500(ai, COMMAND, pCmd->cmd);

	while (max_tries-- && (IN4500(ai, EVSTAT) & EV_CMD) == 0) {
		if ((IN4500(ai, COMMAND)) == pCmd->cmd)
			OUT4500(ai, COMMAND, pCmd->cmd);
		if (!in_atomic() && (max_tries & 255) == 0)
			schedule();
	}

	if ( max_tries == -1 ) {
		airo_print_err(ai->dev->name,
			"Max tries exceeded when issuing command");
		if (IN4500(ai, COMMAND) & COMMAND_BUSY)
			OUT4500(ai, EVACK, EV_CLEARCOMMANDBUSY);
		return ERROR;
	}

	pRsp->status = IN4500(ai, STATUS);
	pRsp->rsp0 = IN4500(ai, RESP0);
	pRsp->rsp1 = IN4500(ai, RESP1);
	pRsp->rsp2 = IN4500(ai, RESP2);
	if ((pRsp->status & 0xff00)!=0 && pCmd->cmd != CMD_SOFTRESET)
		airo_print_err(ai->dev->name,
			"cmd:%x status:%x rsp0:%x rsp1:%x rsp2:%x",
			pCmd->cmd, pRsp->status, pRsp->rsp0, pRsp->rsp1,
			pRsp->rsp2);

	if (IN4500(ai, COMMAND) & COMMAND_BUSY) {
		OUT4500(ai, EVACK, EV_CLEARCOMMANDBUSY);
	}
	OUT4500(ai, EVACK, EV_CMD);

	return SUCCESS;
}
