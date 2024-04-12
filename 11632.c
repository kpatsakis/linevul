static void histogramMutationEventUsage(const unsigned short& listenerTypes)
{
    HistogramSupport::histogramEnumeration("DOMAPI.PerDocumentMutationEventUsage.DOMSubtreeModified", static_cast<bool>(listenerTypes & Document::DOMSUBTREEMODIFIED_LISTENER), 2);
    HistogramSupport::histogramEnumeration("DOMAPI.PerDocumentMutationEventUsage.DOMNodeInserted", static_cast<bool>(listenerTypes & Document::DOMNODEINSERTED_LISTENER), 2);
    HistogramSupport::histogramEnumeration("DOMAPI.PerDocumentMutationEventUsage.DOMNodeRemoved", static_cast<bool>(listenerTypes & Document::DOMNODEREMOVED_LISTENER), 2);
    HistogramSupport::histogramEnumeration("DOMAPI.PerDocumentMutationEventUsage.DOMNodeRemovedFromDocument", static_cast<bool>(listenerTypes & Document::DOMNODEREMOVEDFROMDOCUMENT_LISTENER), 2);
    HistogramSupport::histogramEnumeration("DOMAPI.PerDocumentMutationEventUsage.DOMNodeInsertedIntoDocument", static_cast<bool>(listenerTypes & Document::DOMNODEINSERTEDINTODOCUMENT_LISTENER), 2);
    HistogramSupport::histogramEnumeration("DOMAPI.PerDocumentMutationEventUsage.DOMCharacterDataModified", static_cast<bool>(listenerTypes & Document::DOMCHARACTERDATAMODIFIED_LISTENER), 2);
}
