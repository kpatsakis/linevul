void Document::AddAXContext(AXContext* context) {
  DCHECK_EQ(&AXObjectCacheOwner(), this);

  if (!GetLayoutView())
    return;

  ax_contexts_.push_back(context);
  if (ax_contexts_.size() != 1)
    return;

  if (!ax_object_cache_)
    ax_object_cache_ = AXObjectCache::Create(*this);
}
