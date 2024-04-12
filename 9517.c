expand_check_condition(uschar *condition, uschar *m1, uschar *m2)
{
int rc;
uschar *ss = expand_string(condition);
if (ss == NULL)
  {
  if (!expand_string_forcedfail && !search_find_defer)
    log_write(0, LOG_MAIN|LOG_PANIC, "failed to expand condition \"%s\" "
      "for %s %s: %s", condition, m1, m2, expand_string_message);
  return FALSE;
  }
rc = ss[0] != 0 && Ustrcmp(ss, "0") != 0 && strcmpic(ss, US"no") != 0 &&
  strcmpic(ss, US"false") != 0;
return rc;
}
