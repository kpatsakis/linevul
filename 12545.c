free_config_tinker(
	config_tree *ptree
	)
{
	FREE_ATTR_VAL_FIFO(ptree->tinker);
}
