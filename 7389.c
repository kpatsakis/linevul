  std::unique_ptr<views::Widget> CreateWindowWidget(const gfx::Rect& bounds) {
    std::unique_ptr<views::Widget> widget(new views::Widget);
    views::Widget::InitParams params;
    params.bounds = bounds;
    params.type = views::Widget::InitParams::TYPE_WINDOW;
    params.ownership = views::Widget::InitParams::WIDGET_OWNS_NATIVE_WIDGET;
    widget->Init(params);
    widget->Show();
    aura::Window* window = widget->GetNativeWindow();
    window->SetProperty(aura::client::kTopViewInset, kHeaderHeight);
    ParentWindowInPrimaryRootWindow(window);
    return widget;
  }
