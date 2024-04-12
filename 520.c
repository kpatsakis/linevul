HTMLHeadElement* Document::head()
{
    Node* de = documentElement();
    if (!de)
        return 0;

    for (Node* e = de->firstChild(); e; e = e->nextSibling())
        if (e->hasTagName(headTag))
            return static_cast<HTMLHeadElement*>(e);

    return 0;
}
