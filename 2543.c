void RenderBlock::finishDelayUpdateScrollInfo()
{
    --gDelayUpdateScrollInfo;
    ASSERT(gDelayUpdateScrollInfo >= 0);
    if (gDelayUpdateScrollInfo == 0) {
        ASSERT(gDelayedUpdateScrollInfoSet);

        OwnPtr<DelayedUpdateScrollInfoSet> infoSet(adoptPtr(gDelayedUpdateScrollInfoSet));
        gDelayedUpdateScrollInfoSet = 0;

        for (DelayedUpdateScrollInfoSet::iterator it = infoSet->begin(); it != infoSet->end(); ++it) {
            RenderBlock* block = *it;
            if (block->hasOverflowClip()) {
                block->layer()->scrollableArea()->updateAfterLayout();
            }
        }
    }
}
