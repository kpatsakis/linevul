  TabContentsWrapper* CreateTabContents() {
    return Browser::TabContentsFactory(profile(), NULL, 0, NULL, NULL);
  }
