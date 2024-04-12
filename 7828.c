HTMLElement& toHTMLElement(FormAssociatedElement& associatedElement)
{
    return const_cast<HTMLElement&>(toHTMLElement(static_cast<const FormAssociatedElement&>(associatedElement)));
}
