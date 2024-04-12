void HTMLSelectElement::accessKeySetSelectedIndex(int index)
{    
    if (!focused())
        accessKeyAction(false);
    
    const Vector<HTMLElement*>& items = listItems();
    int listIndex = optionToListIndex(index);
    if (listIndex >= 0) {
        HTMLElement* element = items[listIndex];
        if (element->hasTagName(optionTag)) {
            if (toHTMLOptionElement(element)->selected())
                toHTMLOptionElement(element)->setSelectedState(false);
            else
                selectOption(index, DispatchChangeEvent | UserDriven);
        }
    }

    if (usesMenuList())
        dispatchChangeEventForMenuList();
    else
        listBoxOnChange();

    scrollToSelection();
}
