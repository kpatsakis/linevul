EnumerationHistogram& HTMLMediaElement::showControlsHistogram() const {
  if (isHTMLVideoElement()) {
    DEFINE_STATIC_LOCAL(EnumerationHistogram, histogram,
                        ("Media.Controls.Show.Video", MediaControlsShowMax));
    return histogram;
  }

  DEFINE_STATIC_LOCAL(EnumerationHistogram, histogram,
                      ("Media.Controls.Show.Audio", MediaControlsShowMax));
  return histogram;
}
