  SendThumbnailTask(HWND aeropeek_window,
                    const gfx::Rect& content_bounds,
                    const gfx::Size& aeropeek_size,
                    const SkBitmap& tab_bitmap,
                    base::WaitableEvent* ready)
      : aeropeek_window_(aeropeek_window),
        content_bounds_(content_bounds),
        aeropeek_size_(aeropeek_size),
        tab_bitmap_(tab_bitmap),
        ready_(ready) {
  }
