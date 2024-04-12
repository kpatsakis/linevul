const AtomicString& MediaControlCastButtonElement::shadowPseudoId() const {
  DEFINE_STATIC_LOCAL(AtomicString, id_nonOverlay,
                      ("-internal-media-controls-cast-button"));
  DEFINE_STATIC_LOCAL(AtomicString, id_overlay,
                      ("-internal-media-controls-overlay-cast-button"));
  return m_isOverlayButton ? id_overlay : id_nonOverlay;
}
