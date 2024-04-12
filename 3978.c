WebMediaPlayer::TrackId HTMLMediaElement::GetSelectedVideoTrackId() {
  DCHECK(HasSelectedVideoTrack());

  int selected_track_index = video_tracks_->selectedIndex();
  VideoTrack* track =
      video_tracks_->AnonymousIndexedGetter(selected_track_index);
  return track->id();
}
