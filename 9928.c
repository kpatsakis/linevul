void HTMLInputElement::endEditing()
{
    if (!isTextField())
        return;

    if (Frame* frame = document()->frame())
        frame->editor()->textFieldDidEndEditing(this);
}
