static void srpt_queue_tm_rsp(struct se_cmd *cmd)
{
	srpt_queue_response(cmd);
}
