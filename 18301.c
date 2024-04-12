static void airo_networks_free(struct airo_info *ai)
{
	kfree(ai->networks);
	ai->networks = NULL;
}
