void ChromotingInstance::HandlePauseVideo(const base::DictionaryValue& data) {
  if (!data.HasKey("pause")) {
    LOG(ERROR) << "Invalid pauseVideo.";
    return;
  }
  HandleVideoControl(data);
}
