void OutOfProcessInstance::NotifyNumberOfFindResultsChanged(int total,
                                                            bool final_result) {
  if (final_result) {
    NumberOfFindResultsChanged(total, final_result);
    SetTickmarks(tickmarks_);
    return;
  }

  if (recently_sent_find_update_)
    return;

  NumberOfFindResultsChanged(total, final_result);
  SetTickmarks(tickmarks_);
  recently_sent_find_update_ = true;
  pp::CompletionCallback callback =
      timer_factory_.NewCallback(
          &OutOfProcessInstance::ResetRecentlySentFindUpdate);
  pp::Module::Get()->core()->CallOnMainThread(kFindResultCooldownMs,
                                              callback, 0);
}
