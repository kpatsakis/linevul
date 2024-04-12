WebPage::~WebPage()
{
    deleteGuardedObject(d);
    d = 0;
}
