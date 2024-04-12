  void Navigate(const char* url, int page_id) {
    contents()->TestDidNavigate(
        contents()->GetRenderViewHost(), page_id, GURL(url),
        content::PAGE_TRANSITION_TYPED);
  }
