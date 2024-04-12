void HTMLInputElement::willChangeForm()
{
    removeFromRadioButtonGroup();
    HTMLTextFormControlElement::willChangeForm();
}
