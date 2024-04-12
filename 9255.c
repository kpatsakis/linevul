void RenderBlock::addPercentHeightDescendant(RenderBox* descendant)
{
    insertIntoTrackedRendererMaps(descendant, gPercentHeightDescendantsMap, gPercentHeightContainerMap);
}
