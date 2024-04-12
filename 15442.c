static int cmd_resize(void *data, const char *input) {
	RCore *core = (RCore *)data;
	ut64 oldsize, newsize = 0;
	st64 delta = 0;
	int grow, ret;

	if (core->file && core->file->desc)
		oldsize = r_io_desc_size (core->io, core->file->desc);
	else oldsize = 0;
	switch (*input) {
	case '2':
		r_sys_cmdf ("radare%s", input);
		return true;
	case 'm':
		if (input[1] == ' ')
			r_file_rm (input + 2);
		else eprintf ("Usage: rm [file]   # removes a file\n");
		return true;
	case '\0':
		if (core->file && core->file->desc) {
			if (oldsize != -1) {
				r_cons_printf ("%"PFMT64d"\n", oldsize);
			}
		}
		return true;
	case '+':
	case '-':
		delta = (st64)r_num_math (core->num, input);
		newsize = oldsize + delta;
		break;
	case ' ':
		newsize = r_num_math (core->num, input + 1);
		if (newsize == 0) {
			if (input[1] == '0')
				eprintf ("Invalid size\n");
			return false;
		}
		break;
	default:
	case '?':{
		const char* help_msg[] = {
			"Usage:", "r[+-][ size]", "Resize file",
			"r", "", "display file size",
			"r", " size", "expand or truncate file to given size",
			"r-", "num", "remove num bytes, move following data down",
			"r+", "num", "insert num bytes, move following data up",
			"rm" ," [file]", "remove file",
			"r2" ," [file]", "launch r2",
			NULL};
		r_core_cmd_help (core, help_msg);
		}
		return true;
	}

	grow = (newsize > oldsize);
	if (grow) {
		ret = r_io_resize (core->io, newsize);
		if (ret < 1)
			eprintf ("r_io_resize: cannot resize\n");
	}

	if (delta && core->offset < newsize)
		r_io_shift (core->io, core->offset, grow?newsize:oldsize, delta);

	if (!grow) {
		ret = r_io_resize (core->io, newsize);
		if (ret < 1)
			eprintf ("r_io_resize: cannot resize\n");
	}

	if (newsize < core->offset+core->blocksize ||
			oldsize < core->offset + core->blocksize) {
		r_core_block_read (core);
	}
	return true;
}
