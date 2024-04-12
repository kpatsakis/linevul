void HTMLSelectElement::dispatchBlurEvent(PassRefPtr<Node> newFocusedNode)
{
    if (usesMenuList())
        dispatchChangeEventForMenuList();
    HTMLFormControlElementWithState::dispatchBlurEvent(newFocusedNode);
}
