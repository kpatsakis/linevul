bool HarfBuzzShaper::fillGlyphBuffer(GlyphBuffer* glyphBuffer)
{
    ASSERT(glyphBuffer);

    unsigned numRuns = m_harfBuzzRuns.size();
    float advanceSoFar = 0;
    for (unsigned runIndex = 0; runIndex < numRuns; ++runIndex) {
        HarfBuzzRun* currentRun = m_harfBuzzRuns[m_run.ltr() ? runIndex : numRuns - runIndex - 1].get();
        if (!currentRun->numGlyphs())
            continue;
        advanceSoFar += forTextEmphasis()
            ? fillGlyphBufferForTextEmphasis(glyphBuffer, currentRun, advanceSoFar)
            : fillGlyphBufferFromHarfBuzzRun(glyphBuffer, currentRun, advanceSoFar);
    }
    return glyphBuffer->size();
}
