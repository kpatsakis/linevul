void HTMLDocument::setBodyAttribute(const QualifiedName& name, const AtomicString& value)
{
    if (HTMLBodyElement* body = htmlBodyElement()) {
        if (body->fastGetAttribute(name) != value)
            body->setAttribute(name, value);
    }
}
