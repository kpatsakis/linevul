PassRefPtrWillBeRawPtr<Element> Document::createElement(const AtomicString& name, ExceptionState& exceptionState)
{
    if (!isValidName(name)) {
        exceptionState.throwDOMException(InvalidCharacterError, "The tag name provided ('" + name + "') is not a valid name.");
        return nullptr;
    }

    if (isXHTMLDocument() || isHTMLDocument())
        return HTMLElementFactory::createHTMLElement(convertLocalName(name), *this, 0, false);

    return Element::create(QualifiedName(nullAtom, name, nullAtom), this);
}
