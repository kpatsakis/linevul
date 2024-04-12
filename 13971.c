static int lua_auth_checker_harness_first(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "auth_checker", AP_LUA_HOOK_FIRST);
}
