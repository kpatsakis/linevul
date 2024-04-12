base::string16 GetDisplaySize(int64_t display_id) {
  display::DisplayManager* display_manager = GetDisplayManager();

  const display::Display* display =
      &display_manager->GetDisplayForId(display_id);

  bool mirroring = display_manager->mirroring_display_id() == display_id;
  DCHECK(!mirroring);
  if (mirroring)
    return base::string16();

  DCHECK(display->is_valid());
  return base::UTF8ToUTF16(display->size().ToString());
}
