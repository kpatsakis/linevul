TabStrip::TabStrip(TabStripController* controller)
    : controller_(controller),
      newtab_button_(NULL),
      current_unselected_width_(Tab::GetStandardSize().width()),
      current_selected_width_(Tab::GetStandardSize().width()),
      available_width_for_tabs_(-1),
      in_tab_close_(false),
      animation_container_(new gfx::AnimationContainer()),
      bounds_animator_(this),
      layout_type_(TAB_STRIP_LAYOUT_SHRINK),
      adjust_layout_(false),
      reset_to_shrink_on_exit_(false),
      mouse_move_count_(0),
      immersive_style_(false) {
  Init();
}
