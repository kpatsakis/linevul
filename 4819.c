void DOMPatchSupport::patchDocument(Document* document, const String& markup)
{
    InspectorHistory history;
    DOMEditor domEditor(&history);
    DOMPatchSupport patchSupport(&domEditor, document);
    patchSupport.patchDocument(markup);
}
