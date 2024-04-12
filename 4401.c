void InfoBarCountObserver::CheckCount() {
  InfoBarTabHelper* infobar_tab_helper =
      InfoBarTabHelper::FromWebContents(tab_contents_->web_contents());
  if (infobar_tab_helper->GetInfoBarCount() != target_count_)
    return;

  if (automation_) {
    AutomationMsg_WaitForInfoBarCount::WriteReplyParams(reply_message_.get(),
                                                        true);
    automation_->Send(reply_message_.release());
  }
  delete this;
}
