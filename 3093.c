Document::~Document() {
  DCHECK(!GetLayoutView());
  DCHECK(!ParentTreeScope());
  DCHECK(!ax_object_cache_);

  InstanceCounters::DecrementCounter(InstanceCounters::kDocumentCounter);
}
