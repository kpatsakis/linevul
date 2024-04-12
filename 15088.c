base::i18n::TextDirection WebTextDirectionToChromeTextDirection(
    WebKit::WebTextDirection dir) {
  switch (dir) {
    case WebKit::WebTextDirectionLeftToRight:
      return base::i18n::LEFT_TO_RIGHT;
    case WebKit::WebTextDirectionRightToLeft:
      return base::i18n::RIGHT_TO_LEFT;
    default:
      NOTREACHED();
      return base::i18n::UNKNOWN_DIRECTION;
  }
}
