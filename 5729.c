void XSSAuditor::InitForFragment() {
  DCHECK(IsMainThread());
  DCHECK_EQ(state_, kUninitialized);
  state_ = kFilteringTokens;
  DCHECK(!is_enabled_);
}
