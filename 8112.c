void Textfield::ShowContextMenuForView(View* source,
                                       const gfx::Point& point,
                                       ui::MenuSourceType source_type) {
  UpdateContextMenu();
  context_menu_runner_->RunMenuAt(GetWidget(), NULL,
                                  gfx::Rect(point, gfx::Size()),
                                  MENU_ANCHOR_TOPLEFT, source_type);
}
