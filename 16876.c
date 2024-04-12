void HTMLInputElement::setSize(unsigned size)
{
    setAttribute(sizeAttr, String::number(size));
}
