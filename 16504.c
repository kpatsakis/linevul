static void set_ethernet_addr(pegasus_t *pegasus)
{
	__u8 node_id[6];

	if (pegasus->features & PEGASUS_II) {
		get_registers(pegasus, 0x10, sizeof(node_id), node_id);
	} else {
		get_node_id(pegasus, node_id);
		set_registers(pegasus, EthID, sizeof(node_id), node_id);
	}
	memcpy(pegasus->net->dev_addr, node_id, sizeof(node_id));
}
