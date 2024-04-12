RenderBlock* RenderBlock::clone() const
{
    RenderBlock* cloneBlock;
    if (isAnonymousBlock()) {
        cloneBlock = createAnonymousBlock();
        cloneBlock->setChildrenInline(childrenInline());
    }
    else {
        RenderObject* cloneRenderer = toElement(node())->createRenderer(style());
        cloneBlock = toRenderBlock(cloneRenderer);
        cloneBlock->setStyle(style());

        cloneBlock->setChildrenInline(cloneBlock->firstChild() ? cloneBlock->firstChild()->isInline() : childrenInline());
    }
    cloneBlock->setFlowThreadState(flowThreadState());
    return cloneBlock;
}
