void PDFiumEngine::StartFind(const std::string& text, bool case_sensitive) {
  DCHECK(!text.empty());

  if (pages_.empty())
    return;

  bool first_search = (current_find_text_ != text);
  int character_to_start_searching_from = 0;
  if (first_search) {
    std::vector<PDFiumRange> old_selection = selection_;
    StopFind();
    current_find_text_ = text;

    if (old_selection.empty()) {
      next_page_to_search_ = 0;
      last_page_to_search_ = pages_.size() - 1;
      last_character_index_to_search_ = -1;
    } else {
      next_page_to_search_ = old_selection[0].page_index();
      last_character_index_to_search_ = old_selection[0].char_index();
      character_to_start_searching_from = old_selection[0].char_index();
      last_page_to_search_ = next_page_to_search_;
    }
  }

  int current_page = next_page_to_search_;

  if (pages_[current_page]->available()) {
    base::string16 str = base::UTF8ToUTF16(text);
    if (0) {
      SearchUsingPDFium(str, case_sensitive, first_search,
                        character_to_start_searching_from, current_page);
    } else {
      SearchUsingICU(str, case_sensitive, first_search,
                     character_to_start_searching_from, current_page);
    }

    if (!IsPageVisible(current_page))
      pages_[current_page]->Unload();
  }

  if (next_page_to_search_ != last_page_to_search_ ||
      (first_search && last_character_index_to_search_ != -1)) {
    ++next_page_to_search_;
  }

  if (next_page_to_search_ == static_cast<int>(pages_.size()))
    next_page_to_search_ = 0;
  bool end_of_search =
      next_page_to_search_ == last_page_to_search_ &&
      ((pages_.size() == 1 && last_character_index_to_search_ == -1) ||
       (pages_.size() == 1 && !first_search) ||
       (pages_.size() > 1 && current_page == next_page_to_search_));

  if (end_of_search) {
    client_->NotifyNumberOfFindResultsChanged(find_results_.size(), true);
  } else {
    pp::CompletionCallback callback =
        find_factory_.NewCallback(&PDFiumEngine::ContinueFind);
    pp::Module::Get()->core()->CallOnMainThread(0, callback,
                                                case_sensitive ? 1 : 0);
  }
}
