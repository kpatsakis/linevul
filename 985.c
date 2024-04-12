static const char *register_filter_function_hook(const char *filter,
                                                     cmd_parms *cmd,
                                                     void *_cfg,
                                                     const char *file,
                                                     const char *function,
                                                     int direction)
{
    ap_lua_filter_handler_spec *spec;
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
   
    spec = apr_pcalloc(cmd->pool, sizeof(ap_lua_filter_handler_spec));
    spec->file_name = apr_pstrdup(cmd->pool, file);
    spec->function_name = apr_pstrdup(cmd->pool, function);
    spec->filter_name = filter;

    *(ap_lua_filter_handler_spec **) apr_array_push(cfg->mapped_filters) = spec;
    /* TODO: Make it work on other types than just AP_FTYPE_RESOURCE? */
    if (direction == AP_LUA_FILTER_OUTPUT) {
        spec->direction = AP_LUA_FILTER_OUTPUT;
        ap_register_output_filter_protocol(filter, lua_output_filter_handle, NULL, AP_FTYPE_RESOURCE,
                                            AP_FILTER_PROTO_CHANGE|AP_FILTER_PROTO_CHANGE_LENGTH);
    }
    else {
        spec->direction = AP_LUA_FILTER_INPUT;
        ap_register_input_filter(filter, lua_input_filter_handle, NULL, AP_FTYPE_RESOURCE);
    }
    return NULL;
}
