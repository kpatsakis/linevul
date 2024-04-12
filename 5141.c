void HeadlessPrintManager::ReleaseJob(PrintResult result) {
  if (!callback_) {
    DLOG(ERROR) << "ReleaseJob is called when callback_ is null. Check whether "
                   "ReleaseJob is called more than once.";
    return;
  }

  if (result == PRINT_SUCCESS)
    callback_.Run(result, std::move(data_));
  else
    callback_.Run(result, std::string());
  printing_rfh_->Send(new PrintMsg_PrintingDone(printing_rfh_->GetRoutingID(),
                                                result == PRINT_SUCCESS));
  Reset();
}
