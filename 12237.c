  TabAnimation(TabStripGtk* tabstrip, Type type)
      : tabstrip_(tabstrip),
        animation_(this),
        start_selected_width_(0),
        start_unselected_width_(0),
        end_selected_width_(0),
        end_unselected_width_(0),
        layout_on_completion_(false),
        type_(type) {
  }
