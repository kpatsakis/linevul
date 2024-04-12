bool HTMLMediaElement::HasClosedCaptions() const {
  if (!text_tracks_)
    return false;

  for (unsigned i = 0; i < text_tracks_->length(); ++i) {
    if (text_tracks_->AnonymousIndexedGetter(i)->CanBeRendered())
      return true;
  }

  return false;
}
