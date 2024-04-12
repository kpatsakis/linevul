void RenderBlock::insertIntoTrackedRendererMaps(RenderBox* descendant, TrackedDescendantsMap*& descendantsMap, TrackedContainerMap*& containerMap)
{
    if (!descendantsMap) {
        descendantsMap = new TrackedDescendantsMap;
        containerMap = new TrackedContainerMap;
    }

    TrackedRendererListHashSet* descendantSet = descendantsMap->get(this);
    if (!descendantSet) {
        descendantSet = new TrackedRendererListHashSet;
        descendantsMap->set(this, adoptPtr(descendantSet));
    }
    bool added = descendantSet->add(descendant).isNewEntry;
    if (!added) {
        ASSERT(containerMap->get(descendant));
        ASSERT(containerMap->get(descendant)->contains(this));
        return;
    }

    HashSet<RenderBlock*>* containerSet = containerMap->get(descendant);
    if (!containerSet) {
        containerSet = new HashSet<RenderBlock*>;
        containerMap->set(descendant, adoptPtr(containerSet));
    }
    ASSERT(!containerSet->contains(this));
    containerSet->add(this);
}
