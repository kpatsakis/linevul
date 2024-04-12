static __exit void veth_exit(void)
{
	rtnl_link_unregister(&veth_link_ops);
}
