String WebPageSerializerImpl::preActionBeforeSerializeEndTag(
    const Element* element, SerializeDomParam* param, bool* needSkip)
{
    String result;

    *needSkip = false;
    if (!param->isHTMLDocument)
        return result;
    if (param->skipMetaElement == element) {
        *needSkip = true;
    } else if (isHTMLScriptElement(*element) || isHTMLScriptElement(*element)) {
        ASSERT(param->isInScriptOrStyleTag);
        param->isInScriptOrStyleTag = false;
    }

    return result;
}
