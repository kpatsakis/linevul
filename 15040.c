  gfx::Rect GetTransformedBounds(aura::Window* window) {
    gfx::Rect bounds_in_screen = window->layer()->bounds();
    ::wm::ConvertRectToScreen(window->parent(), &bounds_in_screen);
    gfx::RectF bounds(bounds_in_screen);
    gfx::Transform transform(gfx::TransformAboutPivot(
        gfx::ToFlooredPoint(bounds.origin()), window->layer()->transform()));
    transform.TransformRect(&bounds);
    return gfx::ToEnclosingRect(bounds);
  }
