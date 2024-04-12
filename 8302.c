void iscsi_print_params(struct iscsi_param_list *param_list)
{
	struct iscsi_param *param;

	list_for_each_entry(param, &param_list->param_list, p_list)
		pr_debug("%s: %s\n", param->name, param->value);
}
