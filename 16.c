static VirtualKeyboardType keyboardTypeAttribute(const WebCore::Element* element)
{
    DEFINE_STATIC_LOCAL(QualifiedName, keyboardTypeAttr, (nullAtom, "data-blackberry-virtual-keyboard-type", nullAtom));

    if (element->fastHasAttribute(keyboardTypeAttr)) {
        AtomicString attributeString = element->fastGetAttribute(keyboardTypeAttr);
        return convertStringToKeyboardType(attributeString);
    }

    if (element->isFormControlElement()) {
        const HTMLFormControlElement* formElement = static_cast<const HTMLFormControlElement*>(element);
        if (formElement->form() && formElement->form()->fastHasAttribute(keyboardTypeAttr)) {
            AtomicString attributeString = formElement->form()->fastGetAttribute(keyboardTypeAttr);
            return convertStringToKeyboardType(attributeString);
        }
    }

    return VKBTypeNotSet;
}
