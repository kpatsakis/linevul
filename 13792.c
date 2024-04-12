void MediaStreamManager::Aborted(MediaStreamType stream_type,
                                 int capture_session_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  DVLOG(1) << "Aborted({stream_type = " << stream_type << "} "
           << "{capture_session_id = " << capture_session_id << "})";
  StopDevice(stream_type, capture_session_id);
}
