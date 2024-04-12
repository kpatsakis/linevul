static void logConsoleError(ScriptExecutionContext* context, const String& message)
{
    if (!context)
        return;
    context->addConsoleMessage(JSMessageSource, ErrorMessageLevel, message);
}
