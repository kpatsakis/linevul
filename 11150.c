unsigned long long Timing::loadEventEnd() const
{
    DocumentLoadTiming* timing = documentLoadTiming();
    if (!timing)
        return 0;

    return toIntegerMilliseconds(timing->loadEventEnd);
}
