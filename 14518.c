bool ShelfWidget::GetHitTestRects(aura::Window* target,
                                  gfx::Rect* hit_test_rect_mouse,
                                  gfx::Rect* hit_test_rect_touch) {
  DCHECK(login_shelf_view_->visible());
  gfx::Rect login_view_button_bounds =
      login_shelf_view_->get_button_union_bounds();
  aura::Window* source = login_shelf_view_->GetWidget()->GetNativeWindow();
  aura::Window::ConvertRectToTarget(source, target->parent(),
                                    &login_view_button_bounds);
  *hit_test_rect_mouse = login_view_button_bounds;
  *hit_test_rect_touch = login_view_button_bounds;
  return true;
}
