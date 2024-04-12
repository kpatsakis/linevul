void ContextState::SetWindowRectangles(GLenum mode,
                                       size_t count,
                                       const volatile GLint* box) {
  window_rectangles_mode = mode;
  num_window_rectangles = count;
  DCHECK_LE(count, GetMaxWindowRectangles());
  if (count) {
    std::copy(box, &box[count * 4], window_rectangles_.begin());
  }
}
