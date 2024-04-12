HTMLFormControlElement::~HTMLFormControlElement()
{
#if !ENABLE(OILPAN)
#if ENABLE(ASSERT)
    setNeedsWillValidateCheck();
    setNeedsValidityCheck();
#endif
    setForm(0);
#endif
}
