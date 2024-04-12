PassRefPtr<Element> HTMLConstructionSite::attachToCurrent(PassRefPtr<Element> child)
{
    return attach(currentElement(), child);
}
