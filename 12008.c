void RenderProcessHostImpl::RegisterAecDumpConsumerOnUIThread(int id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  aec_dump_consumers_.push_back(id);

  WebRTCInternals* webrtc_internals = WebRTCInternals::GetInstance();
  if (webrtc_internals->IsAudioDebugRecordingsEnabled()) {
    base::FilePath file_with_extensions = GetAecDumpFilePathWithExtensions(
        webrtc_internals->GetAudioDebugRecordingsFilePath());
    EnableAecDumpForId(file_with_extensions, id);
  }
}
