eval_expr(uschar **sptr, BOOL decimal, uschar **error, BOOL endket)
{
uschar *s = *sptr;
int_eximarith_t x = eval_op_or(&s, decimal, error);
if (*error == NULL)
  {
  if (endket)
    {
    if (*s != ')')
      *error = US"expecting closing parenthesis";
    else
      while (isspace(*(++s)));
    }
  else if (*s != 0) *error = US"expecting operator";
  }
*sptr = s;
return x;
}
