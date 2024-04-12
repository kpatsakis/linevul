void HTMLFormControlElement::showValidationMessage()
{
    scrollIntoViewIfNeeded(false);
    RefPtrWillBeRawPtr<HTMLFormControlElement> protector(this);
    focus();
    updateVisibleValidationMessage();
}
