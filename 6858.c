void SVGDocumentExtensions::removeAllElementReferencesForTarget(SVGElement* referencedElement)
{
    ASSERT(referencedElement);
    HashMap<SVGElement*, OwnPtr<HashSet<SVGElement*> > >::iterator it = m_elementDependencies.find(referencedElement);
    if (it == m_elementDependencies.end())
        return;
    ASSERT(it->key == referencedElement);

    m_elementDependencies.remove(it);
}
