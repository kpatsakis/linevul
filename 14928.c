static void __exit exit_ext3_fs(void)
{
	unregister_filesystem(&ext3_fs_type);
	destroy_inodecache();
	exit_ext3_xattr();
}
