mrb_obj_protected_methods(mrb_state *mrb, mrb_value self)
{
  mrb_bool recur = TRUE;
  mrb_get_args(mrb, "|b", &recur);
  return mrb_obj_methods(mrb, recur, self, NOEX_PROTECTED); /* protected attribute not define */
}
