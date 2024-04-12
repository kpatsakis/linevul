void RenderBlockFlow::deleteLineBoxTree()
{
    if (containsFloats())
        m_floatingObjects->clearLineBoxTreePointers();
    RenderBlock::deleteLineBoxTree();
}
