BarProp* LocalDOMWindow::statusbar() const {
  if (!statusbar_)
    statusbar_ = BarProp::Create(GetFrame(), BarProp::kStatusbar);
  return statusbar_.Get();
}
