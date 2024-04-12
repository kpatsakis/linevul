std::set<FilePath> Extension::GetBrowserImages() const {
  std::set<FilePath> image_paths;

  for (ExtensionIconSet::IconMap::const_iterator iter = icons().map().begin();
       iter != icons().map().end(); ++iter) {
    image_paths.insert(FilePath::FromWStringHack(UTF8ToWide(iter->second)));
  }

  DictionaryValue* theme_images = GetThemeImages();
  if (theme_images) {
    for (DictionaryValue::Iterator it(*theme_images); !it.IsAtEnd();
         it.Advance()) {
      std::string val;
      if (it.value().GetAsString(&val))
        image_paths.insert(FilePath::FromWStringHack(UTF8ToWide(val)));
    }
  }

  if (page_action_info() && !page_action_info()->default_icon.empty()) {
    for (ExtensionIconSet::IconMap::const_iterator iter =
             page_action_info()->default_icon.map().begin();
         iter != page_action_info()->default_icon.map().end();
         ++iter) {
       image_paths.insert(FilePath::FromWStringHack(UTF8ToWide(iter->second)));
    }
  }

  const ActionInfo* browser_action = ActionInfo::GetBrowserActionInfo(this);
  if (browser_action && !browser_action->default_icon.empty()) {
    for (ExtensionIconSet::IconMap::const_iterator iter =
             browser_action->default_icon.map().begin();
         iter != browser_action->default_icon.map().end();
         ++iter) {
       image_paths.insert(FilePath::FromWStringHack(UTF8ToWide(iter->second)));
    }
  }

  return image_paths;
}
