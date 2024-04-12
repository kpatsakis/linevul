int32_t InputHandler::finishComposition()
{
    if (!isActiveTextEdit())
        return -1;

    if (!compositionActive())
        return 0;

    removeAttributedTextMarker();

    InputLog(LogLevelInfo, "InputHandler::finishComposition completed");

    return 0;
}
