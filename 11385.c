int main()
{
 struct binder_state *bs;

    bs = binder_open(128*1024);
 if (!bs) {
        ALOGE("failed to open binder driver\n");
 return -1;
 }

 if (binder_become_context_manager(bs)) {
        ALOGE("cannot become context manager (%s)\n", strerror(errno));
 return -1;
 }

    selinux_enabled = is_selinux_enabled();
    sehandle = selinux_android_service_context_handle();
    selinux_status_open(true);

 if (selinux_enabled > 0) {
 if (sehandle == NULL) {
            ALOGE("SELinux: Failed to acquire sehandle. Aborting.\n");
            abort();
 }

 if (getcon(&service_manager_context) != 0) {
            ALOGE("SELinux: Failed to acquire service_manager context. Aborting.\n");
            abort();
 }
 }

 union selinux_callback cb;
    cb.func_audit = audit_callback;
    selinux_set_callback(SELINUX_CB_AUDIT, cb);
    cb.func_log = selinux_log_callback;
    selinux_set_callback(SELINUX_CB_LOG, cb);

    binder_loop(bs, svcmgr_handler);

 return 0;
}
