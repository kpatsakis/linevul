HTMLCanvasElement* Document::getCSSCanvasElement(const String& name)
{
    RefPtr<HTMLCanvasElement>& element = m_cssCanvasElements.add(name, 0).iterator->value;
    if (!element)
        element = HTMLCanvasElement::create(this);
    return element.get();
}
