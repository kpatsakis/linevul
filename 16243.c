void Scrollbar::updateThumb()
{
#ifdef THUMB_POSITION_AFFECTS_BUTTONS
    invalidate();
#else
    theme()->invalidateParts(this, ForwardTrackPart | BackTrackPart | ThumbPart);
#endif
}
