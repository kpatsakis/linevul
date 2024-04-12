void InspectorPageAgent::getResourceTree(ErrorString*, RefPtr<TypeBuilder::Page::FrameResourceTree>& object)
{
    object = buildObjectForFrameTree(m_page->mainFrame());
}
