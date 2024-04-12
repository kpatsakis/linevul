R_API void r_core_cmd_init(RCore *core) {
	struct {
		const char *cmd;
		const char *description;
		r_cmd_callback (cb);
		void (*descriptor_init)(RCore *core);
	} cmds[] = {
		{"!",        "run system command", cmd_system},
		{"_",        "print last output", cmd_last},
		{"#",        "calculate hash", cmd_hash},
		{"$",        "alias", cmd_alias},
		{"%",        "short version of 'env' command", cmd_env},
		{"&",        "tasks", cmd_tasks},
		{"(",        "macro", cmd_macro, cmd_macro_init},
		{"*",        "pointer read/write", cmd_pointer},
		{"-",        "open cfg.editor and run script", cmd_stdin},
		{".",        "interpret", cmd_interpret},
		{"/",        "search kw, pattern aes", cmd_search, cmd_search_init},
		{"=",        "io pipe", cmd_rap},
		{"?",        "help message", cmd_help, cmd_help_init},
		{"\\",       "alias for =!", cmd_rap_run},
		{"'",        "alias for =!", cmd_rap_run},
		{"0x",       "alias for s 0x", cmd_ox},
		{"analysis", "analysis", cmd_anal, cmd_anal_init},
		{"bsize",    "change block size", cmd_bsize},
		{"cmp",      "compare memory", cmd_cmp, cmd_cmp_init},
		{"Code",     "code metadata", cmd_meta, cmd_meta_init},
		{"debug",    "debugger operations", cmd_debug, cmd_debug_init},
		{"eval",     "evaluate configuration variable", cmd_eval, cmd_eval_init},
		{"flag",     "get/set flags", cmd_flag, cmd_flag_init},
		{"g",        "egg manipulation", cmd_egg, cmd_egg_init},
		{"info",     "get file info", cmd_info, cmd_info_init},
		{"kuery",    "perform sdb query", cmd_kuery},
		{"l",       "list files and directories", cmd_ls},
		{"join",    "join the contents of the two files", cmd_join},
		{"head",    "show the top n number of line in file", cmd_head},
		{"L",        "manage dynamically loaded plugins", cmd_plugins},
		{"mount",    "mount filesystem", cmd_mount, cmd_mount_init},
		{"open",     "open or map file", cmd_open, cmd_open_init},
		{"print",    "print current block", cmd_print, cmd_print_init},
		{"Project",  "project", cmd_project, cmd_project_init},
		{"quit",     "exit program session", cmd_quit, cmd_quit_init},
		{"Q",        "alias for q!", cmd_Quit},
		{":",        "long commands starting with :", cmd_colon},
		{"resize",   "change file size", cmd_resize},
		{"seek",     "seek to an offset", cmd_seek, cmd_seek_init},
		{"t",        "type information (cparse)", cmd_type, cmd_type_init},
		{"Text",     "Text log utility", cmd_log, cmd_log_init},
		{"u",        "uname/undo", cmd_uname},
		{"<",        "pipe into RCons.readChar", cmd_pipein},
		{"Visual",   "enter visual mode", cmd_visual},
		{"visualPanels",   "enter visual mode", cmd_panels},
		{"write",    "write bytes", cmd_write, cmd_write_init},
		{"x",        "alias for px", cmd_hexdump},
		{"yank",     "yank bytes", cmd_yank},
		{"zign",     "zignatures", cmd_zign, cmd_zign_init},
	};

	core->rcmd = r_cmd_new ();
	core->rcmd->macro.user = core;
	core->rcmd->macro.num = core->num;
	core->rcmd->macro.cmd = core_cmd0_wrapper;
	core->rcmd->nullcallback = r_core_cmd_nullcallback;
	core->rcmd->macro.cb_printf = (PrintfCallback)r_cons_printf;
	r_cmd_set_data (core->rcmd, core);
	core->cmd_descriptors = r_list_newf (free);
	int i;
	for (i = 0; i < R_ARRAY_SIZE (cmds); i++) {
		r_cmd_add (core->rcmd, cmds[i].cmd, cmds[i].description, cmds[i].cb);
		if (cmds[i].descriptor_init) {
			cmds[i].descriptor_init (core);
		}
	}
	DEFINE_CMD_DESCRIPTOR_SPECIAL (core, $, dollar);
	DEFINE_CMD_DESCRIPTOR_SPECIAL (core, %, percent);
	DEFINE_CMD_DESCRIPTOR_SPECIAL (core, *, star);
	DEFINE_CMD_DESCRIPTOR_SPECIAL (core, ., dot);
	DEFINE_CMD_DESCRIPTOR_SPECIAL (core, =, equal);
	DEFINE_CMD_DESCRIPTOR (core, b);
	DEFINE_CMD_DESCRIPTOR (core, k);
	DEFINE_CMD_DESCRIPTOR (core, r);
	DEFINE_CMD_DESCRIPTOR (core, u);
	DEFINE_CMD_DESCRIPTOR (core, y);
	cmd_descriptor_init (core);
}
