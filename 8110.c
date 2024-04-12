static const char *register_type_checker_block(cmd_parms *cmd, void *_cfg,
                                               const char *line)
{
    return register_named_block_function_hook("type_checker", cmd, _cfg,
                                              line);
}
