mrb_func_basic_p(mrb_state *mrb, mrb_value obj, mrb_sym mid, mrb_func_t func)
{
  mrb_method_t m = mrb_method_search(mrb, mrb_class(mrb, obj), mid);
  struct RProc *p;

  if (MRB_METHOD_UNDEF_P(m)) return FALSE;
  if (MRB_METHOD_FUNC_P(m))
    return MRB_METHOD_FUNC(m) == func;
  p = MRB_METHOD_PROC(m);
  if (MRB_PROC_CFUNC_P(p) && (MRB_PROC_CFUNC(p) == func))
    return TRUE;
  return FALSE;
}
