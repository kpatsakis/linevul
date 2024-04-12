void AppCacheHost::DoPendingSwapCache() {
  DCHECK_EQ(false, pending_swap_cache_callback_.is_null());

  bool success = false;
  if (associated_cache_.get() && associated_cache_->owning_group()) {
    if (associated_cache_->owning_group()->is_obsolete()) {
      success = true;
      AssociateNoCache(GURL());
    } else if (swappable_cache_.get()) {
      DCHECK(swappable_cache_.get() ==
             swappable_cache_->owning_group()->newest_complete_cache());
      success = true;
      AssociateCompleteCache(swappable_cache_.get());
    }
  }

  pending_swap_cache_callback_.Run(success, pending_callback_param_);
  pending_swap_cache_callback_.Reset();
  pending_callback_param_ = NULL;
}
