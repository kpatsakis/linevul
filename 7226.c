void BrowserView::ProcessFullscreen(bool fullscreen,
                                    FullscreenType type,
                                    const GURL& url,
                                    FullscreenExitBubbleType bubble_type) {
  ignore_layout_ = true;
  LocationBarView* location_bar = GetLocationBarView();
#if defined(OS_WIN) && !defined(USE_AURA)
  OmniboxViewWin* omnibox_win =
      GetOmniboxViewWin(location_bar->GetLocationEntry());
#endif

  if (type == FOR_METRO || !fullscreen) {
    fullscreen_bubble_.reset();
  }

  if (fullscreen) {
    views::FocusManager* focus_manager = GetFocusManager();
    DCHECK(focus_manager);
    if (location_bar->Contains(focus_manager->GetFocusedView()))
      focus_manager->ClearFocus();

#if defined(OS_WIN) && !defined(USE_AURA)
    if (omnibox_win) {
      omnibox_win->set_force_hidden(true);
      ShowWindow(omnibox_win->m_hWnd, SW_HIDE);
    }
#endif
  }
#if defined(OS_WIN) && !defined(USE_AURA)
  views::ScopedFullscreenVisibility visibility(frame_->GetNativeView());
#endif

  if (type == FOR_METRO) {
#if defined(OS_WIN) && !defined(USE_AURA)
    static_cast<views::NativeWidgetWin*>(
        frame_->native_widget())->SetMetroSnapFullscreen(fullscreen);
#endif
  } else {
    frame_->SetFullscreen(fullscreen);
  }

  browser_->WindowFullscreenStateChanged();

  if (fullscreen) {
    bool is_kiosk =
        CommandLine::ForCurrentProcess()->HasSwitch(switches::kKioskMode);
    if (!is_kiosk && type != FOR_METRO) {
      fullscreen_bubble_.reset(new FullscreenExitBubbleViews(
          GetWidget(), browser_.get(), url, bubble_type));
    }
  } else {
#if defined(OS_WIN) && !defined(USE_AURA)
    if (omnibox_win) {
      omnibox_win->set_force_hidden(false);
      ShowWindow(omnibox_win->m_hWnd, SW_SHOW);
    }
#endif
  }

  ignore_layout_ = false;
  Layout();
}
