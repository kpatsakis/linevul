void ExtensionAppItem::Move(const ExtensionAppItem* prev,
                            const ExtensionAppItem* next) {
  if (!prev && !next)
    return;  // No reordering necessary

  extensions::ExtensionPrefs* prefs = extensions::ExtensionPrefs::Get(profile_);
  extensions::AppSorting* sorting = GetAppSorting(profile_);

  syncer::StringOrdinal page;
  std::string prev_id, next_id;
  if (!prev) {
    next_id = next->extension_id();
    page = sorting->GetPageOrdinal(next_id);
  } else if (!next) {
    prev_id = prev->extension_id();
    page = sorting->GetPageOrdinal(prev_id);
  } else {
    prev_id = prev->extension_id();
    page = sorting->GetPageOrdinal(prev_id);
    if (page.Equals(sorting->GetPageOrdinal(next->extension_id())))
      next_id = next->extension_id();
  }
  prefs->SetAppDraggedByUser(extension_id_);
  sorting->SetPageOrdinal(extension_id_, page);
  sorting->OnExtensionMoved(extension_id_, prev_id, next_id);
  UpdatePositionFromExtensionOrdering();
 }
