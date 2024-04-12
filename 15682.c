RenderObject* HTMLSelectElement::createRenderer(RenderStyle*)
{
    if (usesMenuList())
        return new (document()->renderArena()) RenderMenuList(this);
    return new (document()->renderArena()) RenderListBox(this);
}
