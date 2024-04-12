CastDetailedView::CastDetailedView(SystemTrayItem* owner,
                                   CastConfigDelegate* cast_config_delegate,
                                   user::LoginStatus login)
    : TrayDetailsView(owner),
      cast_config_delegate_(cast_config_delegate),
      login_(login),
      options_(nullptr) {
  CreateItems();
  UpdateReceiverList();
}
