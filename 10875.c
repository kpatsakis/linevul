void RenderBlock::addVisualOverflowFromTheme()
{
    if (!style()->hasAppearance())
        return;

    IntRect inflatedRect = pixelSnappedBorderBoxRect();
    RenderTheme::theme().adjustRepaintRect(this, inflatedRect);
    addVisualOverflow(inflatedRect);
}
