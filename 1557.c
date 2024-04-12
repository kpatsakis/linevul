void ContextState::EnableDisable(GLenum pname, bool enable) const {
  if (pname == GL_PRIMITIVE_RESTART_FIXED_INDEX &&
      feature_info_->feature_flags().emulate_primitive_restart_fixed_index) {
    return;
  }
  if (enable) {
    api()->glEnableFn(pname);
  } else {
    api()->glDisableFn(pname);
  }
}
