TextRun RenderBlockFlow::constructTextRun(RenderObject* context, const Font& font, const RenderText* text, RenderStyle* style, TextDirection direction, TextRun::ExpansionBehavior expansion)
{
    if (text->is8Bit())
        return constructTextRunInternal(context, font, text->characters8(), text->textLength(), style, direction, expansion);
    return constructTextRunInternal(context, font, text->characters16(), text->textLength(), style, direction, expansion);
}
