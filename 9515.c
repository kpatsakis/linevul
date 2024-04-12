void Document::close(ExceptionState& exceptionState)
{

    if (importLoader()) {
        exceptionState.throwDOMException(InvalidStateError, "Imported document doesn't support close().");
        return;
    }

    if (!scriptableDocumentParser() || !scriptableDocumentParser()->wasCreatedByScript() || !scriptableDocumentParser()->isParsing())
        return;

    explicitClose();
}
