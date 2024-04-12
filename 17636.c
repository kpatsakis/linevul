views::View* TrayCast::CreateDefaultView(user::LoginStatus status) {
  CHECK(default_ == nullptr);
  default_ = new tray::CastDuplexView(this, cast_config_delegate_,
                                      status != user::LOGGED_IN_LOCKED);
  UpdatePrimaryView();
  return default_;
}
