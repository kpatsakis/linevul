WebMediaPlayer::TrackId HTMLMediaElement::AddVideoTrack(
    const WebString& id,
    WebMediaPlayerClient::VideoTrackKind kind,
    const WebString& label,
    const WebString& language,
    bool selected) {
  AtomicString kind_string = VideoKindToString(kind);
  BLINK_MEDIA_LOG << "addVideoTrack(" << (void*)this << ", '" << (String)id
                  << "', '" << (AtomicString)kind_string << "', '"
                  << (String)label << "', '" << (String)language << "', "
                  << BoolString(selected) << ")";

  if (selected && videoTracks().selectedIndex() != -1)
    selected = false;

  VideoTrack* video_track =
      VideoTrack::Create(id, kind_string, label, language, selected);
  videoTracks().Add(video_track);

  return video_track->id();
}
