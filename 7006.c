  bool GetFindBarWindowInfoForBrowser(
      Browser* browser, gfx::Point* position, bool* fully_visible) {
    FindBarTesting* find_bar =
        browser->GetFindBarController()->find_bar()->GetFindBarTesting();
    return find_bar->GetFindBarWindowInfo(position, fully_visible);
  }
