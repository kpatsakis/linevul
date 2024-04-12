FloatRect HarfBuzzShaper::selectionRect(const FloatPoint& point, int height, int from, int to)
{
    float currentX = 0;
    float fromX = 0;
    float toX = 0;
    bool foundFromX = false;
    bool foundToX = false;

    if (m_run.rtl())
        currentX = m_totalWidth;
    for (unsigned i = 0; i < m_harfBuzzRuns.size(); ++i) {
        if (m_run.rtl())
            currentX -= m_harfBuzzRuns[i]->width();
        int numCharacters = m_harfBuzzRuns[i]->numCharacters();
        if (!foundFromX && from >= 0 && from < numCharacters) {
            fromX = m_harfBuzzRuns[i]->xPositionForOffset(from) + currentX;
            foundFromX = true;
        } else {
            from -= numCharacters;
        }

        if (!foundToX && to >= 0 && to < numCharacters) {
            toX = m_harfBuzzRuns[i]->xPositionForOffset(to) + currentX;
            foundToX = true;
        } else {
            to -= numCharacters;
        }

        if (foundFromX && foundToX)
            break;
        if (!m_run.rtl())
            currentX += m_harfBuzzRuns[i]->width();
    }

    if (!foundFromX)
        fromX = 0;
    if (!foundToX)
        toX = m_run.rtl() ? 0 : m_totalWidth;
    if (!foundToX && !foundFromX)
        fromX = toX = 0;

    if (fromX < toX)
        return FloatRect(point.x() + fromX, point.y(), toX - fromX, height);
    return FloatRect(point.x() + toX, point.y(), fromX - toX, height);
}
