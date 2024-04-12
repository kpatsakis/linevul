void Browser::FindReplyHelper(WebContents* web_contents,
                              int request_id,
                              int number_of_matches,
                              const gfx::Rect& selection_rect,
                              int active_match_ordinal,
                              bool final_update) {
  FindTabHelper* find_tab_helper = FindTabHelper::FromWebContents(web_contents);
  if (!find_tab_helper)
    return;

  find_tab_helper->HandleFindReply(request_id,
                                   number_of_matches,
                                   selection_rect,
                                   active_match_ordinal,
                                   final_update);
}
