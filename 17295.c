void OmniboxPopupViewGtk::AcceptLine(size_t line,
                                     WindowOpenDisposition disposition) {
  AutocompleteMatch match = model_->result().match_at(line);
  omnibox_view_->OpenMatch(match, disposition, GURL(), line);
}
