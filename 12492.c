void WebPageSerializerImpl::endTagToString(Element* element,
                                           SerializeDomParam* param)
{
    bool needSkip;
    StringBuilder result;
    result.append(preActionBeforeSerializeEndTag(element, param, &needSkip));
    if (needSkip)
        return;
    if (element->hasChildren() || param->haveAddedContentsBeforeEnd) {
        result.appendLiteral("</");
        result.append(element->nodeName().lower());
        result.append('>');
    } else {
        if (param->isHTMLDocument) {
            result.append('>');
            if (!element->isHTMLElement() || !toHTMLElement(element)->ieForbidsInsertHTML()) {
                result.appendLiteral("</");
                result.append(element->nodeName().lower());
                result.append('>');
            }
        } else {
            result.appendLiteral(" />");
        }
    }
    result.append(postActionAfterSerializeEndTag(element, param));
    saveHTMLContentToBuffer(result.toString(), param);
}
