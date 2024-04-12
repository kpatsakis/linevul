static bool selinux_action_allowed(int s, debugger_request_t* request)
{
 char *scon = NULL, *tcon = NULL;
 const char *tclass = "debuggerd";
 const char *perm;
 bool allowed = false;

 if (request->action <= 0 || request->action >= (sizeof(debuggerd_perms)/sizeof(debuggerd_perms[0]))) {
    ALOGE("SELinux:  No permission defined for debugger action %d", request->action);
 return false;
 }

  perm = debuggerd_perms[request->action];

 if (getpeercon(s, &scon) < 0) {
    ALOGE("Cannot get peer context from socket\n");
 goto out;
 }

 if (getpidcon(request->tid, &tcon) < 0) {
    ALOGE("Cannot get context for tid %d\n", request->tid);
 goto out;
 }

  allowed = (selinux_check_access(scon, tcon, tclass, perm, reinterpret_cast<void*>(request)) == 0);

out:
   freecon(scon);
   freecon(tcon);

    return allowed;
 }
