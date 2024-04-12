int orderly_poweroff(bool force)
{
 int argc;
 char **argv = argv_split(GFP_ATOMIC, poweroff_cmd, &argc);
 static char *envp[] = {
 "HOME=/",
 "PATH=/sbin:/bin:/usr/sbin:/usr/bin",
		NULL
 };
 int ret = -ENOMEM;
 struct subprocess_info *info;

 if (argv == NULL) {
		printk(KERN_WARNING "%s failed to allocate memory for \"%s\"\n",
		       __func__, poweroff_cmd);
 goto out;
 }

	info = call_usermodehelper_setup(argv[0], argv, envp, GFP_ATOMIC);
 if (info == NULL) {
		argv_free(argv);
 goto out;
 }

	call_usermodehelper_setfns(info, NULL, argv_cleanup, NULL);

	ret = call_usermodehelper_exec(info, UMH_NO_WAIT);

  out:
 if (ret && force) {
		printk(KERN_WARNING "Failed to start orderly shutdown: "
 "forcing the issue\n");

 /* I guess this should try to kick off some daemon to
		   sync and poweroff asap.  Or not even bother syncing
		   if we're doing an emergency shutdown? */
		emergency_sync();
		kernel_power_off();
 }

 return ret;
}
