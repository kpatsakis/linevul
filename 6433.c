static void compositionToUnderlines(const Vector<DWORD>& clauses, const Vector<BYTE>& attributes, Vector<CompositionUnderline>& underlines)
{
    if (clauses.isEmpty()) {
        underlines.clear();
        return;
    }
  
    size_t numBoundaries = clauses.size() - 1;
    underlines.resize(numBoundaries);
    for (unsigned i = 0; i < numBoundaries; ++i) {
        underlines[i].startOffset = clauses[i];
        underlines[i].endOffset = clauses[i + 1];
        BYTE attribute = attributes[clauses[i]];
        underlines[i].thick = attribute == ATTR_TARGET_CONVERTED || attribute == ATTR_TARGET_NOTCONVERTED;
        underlines[i].color = Color::black;
    }
}
