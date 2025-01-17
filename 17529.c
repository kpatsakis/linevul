HTMLlineproc0(char *line, struct html_feed_environ *h_env, int internal)
{
    Lineprop mode;
    int cmd;
    struct readbuffer *obuf = h_env->obuf;
    int indent, delta;
    struct parsed_tag *tag;
    Str tokbuf;
    struct table *tbl = NULL;
    struct table_mode *tbl_mode = NULL;
    int tbl_width = 0;
#ifdef USE_M17N
    int is_hangul, prev_is_hangul = 0;
#endif

#ifdef DEBUG
    if (w3m_debug) {
	FILE *f = fopen("zzzproc1", "a");
	fprintf(f, "%c%c%c%c",
		(obuf->flag & RB_PREMODE) ? 'P' : ' ',
		(obuf->table_level >= 0) ? 'T' : ' ',
		(obuf->flag & RB_INTXTA) ? 'X' : ' ',
		(obuf->flag & (RB_SCRIPT | RB_STYLE)) ? 'S' : ' ');
	fprintf(f, "HTMLlineproc1(\"%s\",%d,%lx)\n", line, h_env->limit,
		(unsigned long)h_env);
	fclose(f);
    }
#endif

    tokbuf = Strnew();

  table_start:
    if (obuf->table_level >= 0) {
	int level = min(obuf->table_level, MAX_TABLE - 1);
	tbl = tables[level];
	tbl_mode = &table_mode[level];
	tbl_width = table_width(h_env, level);
    }

    while (*line != '\0') {
	char *str, *p;
	int is_tag = FALSE;
	int pre_mode = (obuf->table_level >= 0) ? tbl_mode->pre_mode :
	    obuf->flag;
	int end_tag = (obuf->table_level >= 0) ? tbl_mode->end_tag :
	    obuf->end_tag;

	if (*line == '<' || obuf->status != R_ST_NORMAL) {
	    /* 
	     * Tag processing
	     */
	    if (obuf->status == R_ST_EOL)
		obuf->status = R_ST_NORMAL;
	    else {
		read_token(h_env->tagbuf, &line, &obuf->status,
			   pre_mode & RB_PREMODE, obuf->status != R_ST_NORMAL);
		if (obuf->status != R_ST_NORMAL)
		    return;
	    }
	    if (h_env->tagbuf->length == 0)
		continue;
	    str = h_env->tagbuf->ptr;
	    if (*str == '<') {
		if (str[1] && REALLY_THE_BEGINNING_OF_A_TAG(str))
		    is_tag = TRUE;
		else if (!(pre_mode & (RB_PLAIN | RB_INTXTA | RB_INSELECT |
				       RB_SCRIPT | RB_STYLE | RB_TITLE))) {
		    line = Strnew_m_charp(str + 1, line, NULL)->ptr;
		    str = "&lt;";
		}
	    }
	}
	else {
	    read_token(tokbuf, &line, &obuf->status, pre_mode & RB_PREMODE, 0);
	    if (obuf->status != R_ST_NORMAL)	/* R_ST_AMP ? */
		obuf->status = R_ST_NORMAL;
	    str = tokbuf->ptr;
	}

	if (pre_mode & (RB_PLAIN | RB_INTXTA | RB_INSELECT | RB_SCRIPT |
			RB_STYLE | RB_TITLE)) {
	    if (is_tag) {
		p = str;
		if ((tag = parse_tag(&p, internal))) {
		    if (tag->tagid == end_tag ||
			(pre_mode & RB_INSELECT && tag->tagid == HTML_N_FORM)
			|| (pre_mode & RB_TITLE
			    && (tag->tagid == HTML_N_HEAD
				|| tag->tagid == HTML_BODY)))
			goto proc_normal;
		}
	    }
	    /* title */
	    if (pre_mode & RB_TITLE) {
		feed_title(str);
		continue;
	    }
	    /* select */
	    if (pre_mode & RB_INSELECT) {
		if (obuf->table_level >= 0)
		    goto proc_normal;
		feed_select(str);
		continue;
	    }
	    if (is_tag) {
		if (strncmp(str, "<!--", 4) && (p = strchr(str + 1, '<'))) {
		    str = Strnew_charp_n(str, p - str)->ptr;
		    line = Strnew_m_charp(p, line, NULL)->ptr;
		}
		is_tag = FALSE;
	    }
	    if (obuf->table_level >= 0)
		goto proc_normal;
	    /* textarea */
	    if (pre_mode & RB_INTXTA) {
		feed_textarea(str);
		continue;
	    }
	    /* script */
	    if (pre_mode & RB_SCRIPT)
		continue;
	    /* style */
	    if (pre_mode & RB_STYLE)
		continue;
	}

      proc_normal:
	if (obuf->table_level >= 0) {
	    /* 
	     * within table: in <table>..</table>, all input tokens
	     * are fed to the table renderer, and then the renderer
	     * makes HTML output.
	     */
	    switch (feed_table(tbl, str, tbl_mode, tbl_width, internal)) {
	    case 0:
		/* </table> tag */
		obuf->table_level--;
		if (obuf->table_level >= MAX_TABLE - 1)
		    continue;
		end_table(tbl);
		if (obuf->table_level >= 0) {
		    struct table *tbl0 = tables[obuf->table_level];
		    str = Sprintf("<table_alt tid=%d>", tbl0->ntable)->ptr;
		    pushTable(tbl0, tbl);
		    tbl = tbl0;
		    tbl_mode = &table_mode[obuf->table_level];
		    tbl_width = table_width(h_env, obuf->table_level);
		    feed_table(tbl, str, tbl_mode, tbl_width, TRUE);
		    continue;
		    /* continue to the next */
		}
		if (obuf->flag & RB_DEL)
		    continue;
		/* all tables have been read */
		if (tbl->vspace > 0 && !(obuf->flag & RB_IGNORE_P)) {
		    int indent = h_env->envs[h_env->envc].indent;
		    flushline(h_env, obuf, indent, 0, h_env->limit);
		    do_blankline(h_env, obuf, indent, 0, h_env->limit);
		}
		save_fonteffect(h_env, obuf);
		renderTable(tbl, tbl_width, h_env);
		restore_fonteffect(h_env, obuf);
		obuf->flag &= ~RB_IGNORE_P;
		if (tbl->vspace > 0) {
		    int indent = h_env->envs[h_env->envc].indent;
		    do_blankline(h_env, obuf, indent, 0, h_env->limit);
		    obuf->flag |= RB_IGNORE_P;
		}
		set_space_to_prevchar(obuf->prevchar);
		continue;
	    case 1:
		/* <table> tag */
		break;
	    default:
		continue;
	    }
	}

	if (is_tag) {
/*** Beginning of a new tag ***/
	    if ((tag = parse_tag(&str, internal)))
		cmd = tag->tagid;
	    else
		continue;
	    /* process tags */
	    if (HTMLtagproc1(tag, h_env) == 0) {
		/* preserve the tag for second-stage processing */
		if (parsedtag_need_reconstruct(tag))
		    h_env->tagbuf = parsedtag2str(tag);
		push_tag(obuf, h_env->tagbuf->ptr, cmd);
	    }
#ifdef ID_EXT
	    else {
		process_idattr(obuf, cmd, tag);
	    }
#endif				/* ID_EXT */
	    obuf->bp.init_flag = 1;
	    clear_ignore_p_flag(cmd, obuf);
	    if (cmd == HTML_TABLE)
		goto table_start;
	    else
		continue;
	}

	if (obuf->flag & (RB_DEL | RB_S))
	    continue;
	while (*str) {
	    mode = get_mctype(str);
	    delta = get_mcwidth(str);
	    if (obuf->flag & (RB_SPECIAL & ~RB_NOBR)) {
		char ch = *str;
		if (!(obuf->flag & RB_PLAIN) && (*str == '&')) {
		    char *p = str;
		    int ech = getescapechar(&p);
		    if (ech == '\n' || ech == '\r') {
			ch = '\n';
			str = p - 1;
		    }
		    else if (ech == '\t') {
			ch = '\t';
			str = p - 1;
		    }
		}
		if (ch != '\n')
		    obuf->flag &= ~RB_IGNORE_P;
		if (ch == '\n') {
		    str++;
		    if (obuf->flag & RB_IGNORE_P) {
			obuf->flag &= ~RB_IGNORE_P;
			continue;
		    }
		    if (obuf->flag & RB_PRE_INT)
			PUSH(' ');
		    else
			flushline(h_env, obuf, h_env->envs[h_env->envc].indent,
				  1, h_env->limit);
		}
		else if (ch == '\t') {
		    do {
			PUSH(' ');
		    } while ((h_env->envs[h_env->envc].indent + obuf->pos)
			     % Tabstop != 0);
		    str++;
		}
		else if (obuf->flag & RB_PLAIN) {
		    char *p = html_quote_char(*str);
		    if (p) {
			push_charp(obuf, 1, p, PC_ASCII);
			str++;
		    }
		    else {
			proc_mchar(obuf, 1, delta, &str, mode);
		    }
		}
		else {
		    if (*str == '&')
			proc_escape(obuf, &str);
		    else
			proc_mchar(obuf, 1, delta, &str, mode);
		}
		if (obuf->flag & (RB_SPECIAL & ~RB_PRE_INT))
		    continue;
	    }
	    else {
		if (!IS_SPACE(*str))
		    obuf->flag &= ~RB_IGNORE_P;
		if ((mode == PC_ASCII || mode == PC_CTRL) && IS_SPACE(*str)) {
		    if (*obuf->prevchar->ptr != ' ') {
			PUSH(' ');
		    }
		    str++;
		}
		else {
#ifdef USE_M17N
		    if (mode == PC_KANJI1)
			is_hangul = wtf_is_hangul((wc_uchar *) str);
		    else
			is_hangul = 0;
		    if (!SimplePreserveSpace && mode == PC_KANJI1 &&
			!is_hangul && !prev_is_hangul &&
			obuf->pos > h_env->envs[h_env->envc].indent &&
			Strlastchar(obuf->line) == ' ') {
			while (obuf->line->length >= 2 &&
			       !strncmp(obuf->line->ptr + obuf->line->length -
					2, "  ", 2)
			       && obuf->pos >= h_env->envs[h_env->envc].indent) {
			    Strshrink(obuf->line, 1);
			    obuf->pos--;
			}
			if (obuf->line->length >= 3 &&
			    obuf->prev_ctype == PC_KANJI1 &&
			    Strlastchar(obuf->line) == ' ' &&
			    obuf->pos >= h_env->envs[h_env->envc].indent) {
			    Strshrink(obuf->line, 1);
			    obuf->pos--;
			}
		    }
		    prev_is_hangul = is_hangul;
#endif
		    if (*str == '&')
			proc_escape(obuf, &str);
		    else
			proc_mchar(obuf, obuf->flag & RB_SPECIAL, delta, &str,
				   mode);
		}
	    }
	    if (need_flushline(h_env, obuf, mode)) {
		char *bp = obuf->line->ptr + obuf->bp.len;
		char *tp = bp - obuf->bp.tlen;
		int i = 0;

		if (tp > obuf->line->ptr && tp[-1] == ' ')
		    i = 1;

		indent = h_env->envs[h_env->envc].indent;
		if (obuf->bp.pos - i > indent) {
		    Str line;
		    append_tags(obuf);
		    line = Strnew_charp(bp);
		    Strshrink(obuf->line, obuf->line->length - obuf->bp.len);
#ifdef FORMAT_NICE
		    if (obuf->pos - i > h_env->limit)
			obuf->flag |= RB_FILL;
#endif				/* FORMAT_NICE */
		    back_to_breakpoint(obuf);
		    flushline(h_env, obuf, indent, 0, h_env->limit);
#ifdef FORMAT_NICE
		    obuf->flag &= ~RB_FILL;
#endif				/* FORMAT_NICE */
		    HTMLlineproc1(line->ptr, h_env);
		}
	    }
	}
    }
    if (!(obuf->flag & (RB_SPECIAL | RB_INTXTA | RB_INSELECT))) {
	char *tp;
	int i = 0;

	if (obuf->bp.pos == obuf->pos) {
	    tp = &obuf->line->ptr[obuf->bp.len - obuf->bp.tlen];
	}
	else {
	    tp = &obuf->line->ptr[obuf->line->length];
	}

	if (tp > obuf->line->ptr && tp[-1] == ' ')
	    i = 1;
	indent = h_env->envs[h_env->envc].indent;
	if (obuf->pos - i > h_env->limit) {
#ifdef FORMAT_NICE
	    obuf->flag |= RB_FILL;
#endif				/* FORMAT_NICE */
	    flushline(h_env, obuf, indent, 0, h_env->limit);
#ifdef FORMAT_NICE
	    obuf->flag &= ~RB_FILL;
#endif				/* FORMAT_NICE */
	}
    }
}
