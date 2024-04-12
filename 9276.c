void WindowTreeHostManager::PostDisplayConfigurationChange() {
  focus_activation_store_->Restore();

  DisplayManager* display_manager = GetDisplayManager();
  display::DisplayLayoutStore* layout_store = display_manager->layout_store();
  if (display_manager->num_connected_displays() > 1) {
    display::DisplayIdList list = display_manager->GetCurrentDisplayIdList();
    const display::DisplayLayout& layout =
        layout_store->GetRegisteredDisplayLayout(list);
    layout_store->UpdateMultiDisplayState(
        list, display_manager->IsInMirrorMode(), layout.default_unified);
    if (display::Screen::GetScreen()->GetNumDisplays() > 1) {
      SetPrimaryDisplayId(layout.primary_id ==
                                  display::Display::kInvalidDisplayID
                              ? list[0]
                              : layout.primary_id);
    }
  }

  for (const display::Display& display :
       display_manager->active_display_list()) {
    bool output_is_secure =
        !display_manager->IsInMirrorMode() && display.IsInternal();
    GetAshWindowTreeHostForDisplayId(display.id())
        ->AsWindowTreeHost()
        ->compositor()
        ->SetOutputIsSecure(output_is_secure);
  }

  FOR_EACH_OBSERVER(Observer, observers_, OnDisplayConfigurationChanged());
  UpdateMouseLocationAfterDisplayChange();
}
