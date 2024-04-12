static inline RenderObject* findFirstLetterBlock(RenderBlock* start)
{
    RenderObject* firstLetterBlock = start;
    while (true) {
        bool canHaveFirstLetterRenderer = firstLetterBlock->style()->hasPseudoStyle(FIRST_LETTER)
            && firstLetterBlock->canHaveGeneratedChildren()
            && (!firstLetterBlock->isFlexibleBox() || firstLetterBlock->isRenderButton());
        if (canHaveFirstLetterRenderer)
            return firstLetterBlock;

        RenderObject* parentBlock = firstLetterBlock->parent();
        if (firstLetterBlock->isReplaced() || !parentBlock || parentBlock->firstChild() != firstLetterBlock ||
            (!parentBlock->isRenderBlockFlow() && !parentBlock->isRenderButton()))
            return 0;
        firstLetterBlock = parentBlock;
    }

    return 0;
}
