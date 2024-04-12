DEFINE_TRACE_WRAPPERS(Document)
{
    visitor->traceWrappers(m_importsController);
    visitor->traceWrappers(m_implementation);
    visitor->traceWrappers(m_styleSheetList);
    visitor->traceWrappers(m_styleEngine);
    visitor->traceWrappers(
        Supplementable<Document>::m_supplements.get(
            FontFaceSet::supplementName()));
    for (int i = 0; i < numNodeListInvalidationTypes; ++i) {
        for (auto list : m_nodeLists[i]) {
            visitor->traceWrappers(list);
        }
    }
    ContainerNode::traceWrappers(visitor);
}
