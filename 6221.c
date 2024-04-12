static int is_valid_veth_mtu(int new_mtu)
{
	return new_mtu >= MIN_MTU && new_mtu <= MAX_MTU;
}
