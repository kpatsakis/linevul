void BackRenderbuffer::Create() {
  ScopedGLErrorSuppressor suppressor("BackRenderbuffer::Create",
                                     decoder_->state_.GetErrorState());
  Destroy();
  api()->glGenRenderbuffersEXTFn(1, &id_);
}
