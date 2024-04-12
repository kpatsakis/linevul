void Resource::MarkAsPreload() {
  DCHECK(!is_unused_preload_);
  is_unused_preload_ = true;
}
