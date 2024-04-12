PassRefPtr<HTMLOptionsCollection> HTMLSelectElement::options()
{
    return static_cast<HTMLOptionsCollection*>(ensureCachedHTMLCollection(SelectOptions).get());
}
