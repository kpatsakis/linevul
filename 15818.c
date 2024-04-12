static int synthesizedBaselineFromContentBox(const RenderBox* box, LineDirectionMode direction)
{
    return direction == HorizontalLine ? box->borderTop() + box->paddingTop() + box->contentHeight() : box->borderRight() + box->paddingRight() + box->contentWidth();
}
