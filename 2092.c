  void SimulateFreezeSignal(content::WebContents* contents) {
    static_cast<TabLifecycleUnitSource::TabLifecycleUnit*>(
        TabLifecycleUnitExternal::FromWebContents(contents))
        ->UpdateLifecycleState(mojom::LifecycleState::kFrozen);
  }
