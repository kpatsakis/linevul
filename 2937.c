alt_merge_opt_exact(OptStr* to, OptStr* add, OptEnv* env)
{
  int i, j, len;

  if (add->len == 0 || to->len == 0) {
    clear_opt_exact(to);
    return ;
  }

  if (! is_equal_mml(&to->mmd, &add->mmd)) {
    clear_opt_exact(to);
    return ;
  }

  for (i = 0; i < to->len && i < add->len; ) {
    if (to->s[i] != add->s[i]) break;
    len = enclen(env->enc, to->s + i);

    for (j = 1; j < len; j++) {
      if (to->s[i+j] != add->s[i+j]) break;
    }
    if (j < len) break;
    i += len;
  }

  if (! add->reach_end || i < add->len || i < to->len) {
    to->reach_end = 0;
  }
  to->len = i;
  if (add->case_fold != 0)
    to->case_fold = 1;
  if (add->good_case_fold == 0)
    to->good_case_fold = 0;

  alt_merge_opt_anc_info(&to->anc, &add->anc);
  if (! to->reach_end) to->anc.right = 0;
}
