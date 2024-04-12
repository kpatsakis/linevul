TabStrip::DropArrow::DropArrow(const BrowserRootView::DropIndex& index,
                               bool point_down,
                               views::Widget* context)
    : index(index), point_down(point_down) {
  arrow_view = new views::ImageView;
  arrow_view->SetImage(GetDropArrowImage(point_down));

  arrow_window = new views::Widget;
  views::Widget::InitParams params(views::Widget::InitParams::TYPE_POPUP);
  params.keep_on_top = true;
  params.opacity = views::Widget::InitParams::TRANSLUCENT_WINDOW;
  params.accept_events = false;
  params.bounds = gfx::Rect(g_drop_indicator_width, g_drop_indicator_height);
  params.context = context->GetNativeWindow();
  arrow_window->Init(params);
  arrow_window->SetContentsView(arrow_view);
}
