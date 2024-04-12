const AtomicString& VideoKindToString(
    WebMediaPlayerClient::VideoTrackKind kind) {
  switch (kind) {
    case WebMediaPlayerClient::VideoTrackKindNone:
      return emptyAtom;
    case WebMediaPlayerClient::VideoTrackKindAlternative:
      return VideoTrack::alternativeKeyword();
    case WebMediaPlayerClient::VideoTrackKindCaptions:
      return VideoTrack::captionsKeyword();
    case WebMediaPlayerClient::VideoTrackKindMain:
      return VideoTrack::mainKeyword();
    case WebMediaPlayerClient::VideoTrackKindSign:
      return VideoTrack::signKeyword();
    case WebMediaPlayerClient::VideoTrackKindSubtitles:
      return VideoTrack::subtitlesKeyword();
    case WebMediaPlayerClient::VideoTrackKindCommentary:
      return VideoTrack::commentaryKeyword();
  }

  NOTREACHED();
  return emptyAtom;
}
