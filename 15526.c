bool HTMLLinkElement::sheetLoaded()
{
    if (!isLoading() && !isDisabled() && !isAlternate()) {
        document()->removePendingSheet();
        return true;
    }
    return false;
}
