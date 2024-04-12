UnloadController::~UnloadController() {
  browser_->tab_strip_model()->RemoveObserver(this);
}
