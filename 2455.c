int relativeLeftOffset(int caretPosition, int leftOffset)
{
    ASSERT(caretPosition >= 0);

    return std::max(0, caretPosition - leftOffset);
}
