void InspectorPageAgent::setDeviceMetricsOverride(ErrorString* errorString, int width, int height, double deviceScaleFactor, bool fitWindow, const bool* optionalTextAutosizing)
{
    const static long maxDimension = 10000000;

    if (width < 0 || height < 0 || width > maxDimension || height > maxDimension) {
        *errorString = "Width and height values must be positive, not greater than " + String::number(maxDimension);
        return;
    }

    if (!width ^ !height) {
        *errorString = "Both width and height must be either zero or non-zero at once";
        return;
    }

    if (deviceScaleFactor <= 0) {
        *errorString = "deviceScaleFactor must be positive";
        return;
    }

    bool textAutosizing = optionalTextAutosizing ? *optionalTextAutosizing : false;

    if (!deviceMetricsChanged(width, height, deviceScaleFactor, fitWindow, textAutosizing))
        return;

    m_state->setLong(PageAgentState::pageAgentScreenWidthOverride, width);
    m_state->setLong(PageAgentState::pageAgentScreenHeightOverride, height);
    m_state->setDouble(PageAgentState::pageAgentDeviceScaleFactorOverride, deviceScaleFactor);
    m_state->setBoolean(PageAgentState::pageAgentFitWindow, fitWindow);
    m_state->setBoolean(PageAgentState::pageAgentTextAutosizingOverride, textAutosizing);

    updateViewMetrics(width, height, deviceScaleFactor, fitWindow, textAutosizing);
}
