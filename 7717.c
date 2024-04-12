PassRefPtr<RenderStyle> StyleResolver::styleForDocument(Document& document, CSSFontSelector* fontSelector)
{
    const Frame* frame = document.frame();

    RefPtr<RenderStyle> documentStyle = RenderStyle::create();
    bool seamlessWithParent = document.shouldDisplaySeamlesslyWithParent();
    if (seamlessWithParent) {
        RenderStyle* iframeStyle = document.seamlessParentIFrame()->renderStyle();
        if (iframeStyle)
            documentStyle->inheritFrom(iframeStyle);
    }

    documentStyle->setDisplay(BLOCK);
    if (!seamlessWithParent) {
        documentStyle->setRTLOrdering(document.visuallyOrdered() ? VisualOrder : LogicalOrder);
        documentStyle->setZoom(frame && !document.printing() ? frame->pageZoomFactor() : 1);
        documentStyle->setLocale(document.contentLanguage());
    }
    documentStyle->setUserModify(document.inDesignMode() ? READ_WRITE : READ_ONLY);

    document.setStyleDependentState(documentStyle.get());
    return documentStyle.release();
}
