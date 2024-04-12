void HTMLConstructionSite::generateImpliedEndTags()
{
    while (hasImpliedEndTag(currentElement()))
        m_openElements.pop();
}
