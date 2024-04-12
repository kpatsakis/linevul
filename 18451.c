static int taskstats_user_cmd(struct sk_buff *skb, struct genl_info *info)
{
	if (info->attrs[TASKSTATS_CMD_ATTR_REGISTER_CPUMASK])
		return cmd_attr_register_cpumask(info);
	else if (info->attrs[TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK])
		return cmd_attr_deregister_cpumask(info);
	else if (info->attrs[TASKSTATS_CMD_ATTR_PID])
		return cmd_attr_pid(info);
	else if (info->attrs[TASKSTATS_CMD_ATTR_TGID])
		return cmd_attr_tgid(info);
	else
		return -EINVAL;
}
