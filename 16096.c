GLES2Implementation::SingleThreadChecker::~SingleThreadChecker() {
  --gles2_implementation_->use_count_;
  CHECK_EQ(0, gles2_implementation_->use_count_);
}
