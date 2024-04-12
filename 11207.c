  void UpdateCachedToken(const std::string& token, const base::TimeDelta& ttl) {
    last_token_ = token;
    last_token_expiry_ = host_->clock_->Now() + ttl;
  }
