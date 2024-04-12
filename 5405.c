free_config_vars(
	config_tree *ptree
	)
{
	FREE_ATTR_VAL_FIFO(ptree->vars);
}
