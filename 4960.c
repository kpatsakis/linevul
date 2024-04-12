void BrowserWindowGtk::ShowDevToolsContainer() {
  bool to_right = devtools_dock_side_ == DEVTOOLS_DOCK_SIDE_RIGHT;
  gtk_paned_pack2(GTK_PANED(to_right ? contents_hsplit_ : contents_vsplit_),
                  devtools_container_->widget(),
                  FALSE,
                  TRUE);
  UpdateDevToolsSplitPosition();
  gtk_widget_show(devtools_container_->widget());
}
