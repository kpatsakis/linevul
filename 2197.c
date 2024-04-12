ndp_find_msgrcv_handler_item(struct ndp *ndp,
			     ndp_msgrcv_handler_func_t func,
			     enum ndp_msg_type msg_type, uint32_t ifindex,
			     void *priv)
{
	struct ndp_msgrcv_handler_item *handler_item;

	list_for_each_node_entry(handler_item, &ndp->msgrcv_handler_list, list)
		if (handler_item->func == func &&
		    handler_item->msg_type == msg_type &&
		    handler_item->ifindex == ifindex &&
		    handler_item->priv == priv)
			return handler_item;
	return NULL;
}
