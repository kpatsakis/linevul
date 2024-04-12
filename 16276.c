int GetIndexOfSingletonTab(browser::NavigateParams* params) {
  if (params->disposition != SINGLETON_TAB)
    return -1;

  GURL rewritten_url(params->url);
  bool reverse_on_redirect = false;
  BrowserURLHandler::GetInstance()->RewriteURLIfNecessary(
      &rewritten_url,
      params->browser->profile(),
      &reverse_on_redirect);

  int start_index = std::max(0, params->browser->active_index());
  int tab_count = params->browser->tab_count();
  for (int i = 0; i < tab_count; ++i) {
    int tab_index = (start_index + i) % tab_count;
    TabContentsWrapper* tab =
        params->browser->GetTabContentsWrapperAt(tab_index);

    url_canon::Replacements<char> replacements;
    if (params->ref_behavior == browser::NavigateParams::IGNORE_REF)
      replacements.ClearRef();
    if (params->path_behavior == browser::NavigateParams::IGNORE_AND_NAVIGATE ||
        params->path_behavior == browser::NavigateParams::IGNORE_AND_STAY_PUT) {
      replacements.ClearPath();
      replacements.ClearQuery();
    }

    if (CompareURLsWithReplacements(tab->tab_contents()->GetURL(),
                                    params->url, replacements) ||
        CompareURLsWithReplacements(tab->tab_contents()->GetURL(),
                                    rewritten_url, replacements)) {
      params->target_contents = tab;
      return tab_index;
    }
  }

  return -1;
}
