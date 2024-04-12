void Document::setEncodingData(const DocumentEncodingData& newData)
{
    if (m_titleElement
        && encoding() != newData.encoding()
        && !ElementTraversal::firstWithin(*m_titleElement)
        && encoding() == Latin1Encoding()
        && m_titleElement->textContent().containsOnlyLatin1()) {

        CString originalBytes = m_titleElement->textContent().latin1();
        OwnPtr<TextCodec> codec = newTextCodec(newData.encoding());
        String correctlyDecodedTitle = codec->decode(originalBytes.data(), originalBytes.length(), DataEOF);
        m_titleElement->setTextContent(correctlyDecodedTitle);
    }

    m_encodingData = newData;

    bool shouldUseVisualOrdering = m_encodingData.encoding().usesVisualOrdering();
    if (shouldUseVisualOrdering != m_visuallyOrdered) {
        m_visuallyOrdered = shouldUseVisualOrdering;
        if (layoutView())
            layoutView()->mutableStyleRef().setRTLOrdering(m_visuallyOrdered ? VisualOrder : LogicalOrder);
        setNeedsStyleRecalc(SubtreeStyleChange, StyleChangeReasonForTracing::create(StyleChangeReason::VisuallyOrdered));
    }
}
