static void add_grep(struct rev_info *revs, const char *ptn, enum grep_pat_token what)
{
	append_grep_pattern(&revs->grep_filter, ptn, "command line", 0, what);
}
