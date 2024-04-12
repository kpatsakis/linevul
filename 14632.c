String WebFrame::counterValue(JSObjectRef element)
{
    if (!toJS(element)->inherits(&JSElement::s_info))
        return String();

    return counterValueForElement(static_cast<JSElement*>(toJS(element))->impl());
}
