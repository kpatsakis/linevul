base::string16 TabLifecycleUnitSource::TabLifecycleUnit::GetTitle() const {
  return GetWebContents()->GetTitle();
}
