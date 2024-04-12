free_config_phone(
	config_tree *ptree
	)
{
	FREE_STRING_FIFO(ptree->phone);
}
