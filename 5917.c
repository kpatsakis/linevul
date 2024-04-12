void LayoutBlockFlow::moveChildrenTo(LayoutBoxModelObject* toBoxModelObject, LayoutObject* startChild, LayoutObject* endChild, LayoutObject* beforeChild, bool fullRemoveInsert)
{
    if (childrenInline())
        deleteLineBoxTree();
    LayoutBoxModelObject::moveChildrenTo(toBoxModelObject, startChild, endChild, beforeChild, fullRemoveInsert);
}
