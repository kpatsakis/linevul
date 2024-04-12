void ShelfLayoutManager::MaybeUpdateShelfBackground(AnimationChangeType type) {
  const ShelfBackgroundType new_background_type(GetShelfBackgroundType());

  if (new_background_type == shelf_background_type_)
    return;

  shelf_background_type_ = new_background_type;
  for (auto& observer : observers_)
    observer.OnBackgroundUpdated(shelf_background_type_, type);
}
