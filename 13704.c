static int lua_map_handler(request_rec *r)
{
    int rc, n = 0;
    apr_pool_t *pool;
    lua_State *L;
    const char *filename, *function_name;
    const char *values[10];
    ap_lua_vm_spec *spec;
    ap_regmatch_t match[10];
    ap_lua_server_cfg *server_cfg = ap_get_module_config(r->server->module_config,
                                                         &lua_module);
    const ap_lua_dir_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                                     &lua_module);
    for (n = 0; n < cfg->mapped_handlers->nelts; n++) {
        ap_lua_mapped_handler_spec *hook_spec =
            ((ap_lua_mapped_handler_spec **) cfg->mapped_handlers->elts)[n];

        if (hook_spec == NULL) {
            continue;
        }
        if (!ap_regexec(hook_spec->uri_pattern, r->uri, 10, match, 0)) {
            int i;
            for (i=0 ; i < 10; i++) {
                if (match[i].rm_eo >= 0) {
                    values[i] = apr_pstrndup(r->pool, r->uri+match[i].rm_so, match[i].rm_eo - match[i].rm_so);
                }
                else values[i] = "";
            }
            filename = ap_lua_interpolate_string(r->pool, hook_spec->file_name, values);
            function_name = ap_lua_interpolate_string(r->pool, hook_spec->function_name, values);
            spec = create_vm_spec(&pool, r, cfg, server_cfg,
                                    filename,
                                    hook_spec->bytecode,
                                    hook_spec->bytecode_len,
                                    function_name,
                                    "mapped handler");
            L = ap_lua_get_lua_state(pool, spec, r);

            if (!L) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02330)
                                "lua: Failed to obtain Lua interpreter for entry function '%s' in %s",
                                function_name, filename);
                ap_lua_release_state(L, spec, r);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            if (function_name != NULL) {
                lua_getglobal(L, function_name);
                if (!lua_isfunction(L, -1)) {
                    ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02331)
                                    "lua: Unable to find entry function '%s' in %s (not a valid function)",
                                    function_name,
                                    filename);
                    ap_lua_release_state(L, spec, r);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

                ap_lua_run_lua_request(L, r);
            }
            else {
                int t;
                ap_lua_run_lua_request(L, r);

                t = lua_gettop(L);
                lua_setglobal(L, "r");
                lua_settop(L, t);
            }

            if (lua_pcall(L, 1, 1, 0)) {
                report_lua_error(L, r);
                ap_lua_release_state(L, spec, r);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            rc = DECLINED;
            if (lua_isnumber(L, -1)) {
                rc = lua_tointeger(L, -1);
            }
            else { 
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02483)
                              "lua: Lua handler %s in %s did not return a value, assuming apache2.OK",
                              function_name,
                              filename);
                rc = OK;
            }
            ap_lua_release_state(L, spec, r);
            if (rc != DECLINED) {
                return rc;
            }
        }
    }
    return DECLINED;
}
