  void AutocompleteSuggestionsReturned(
      const std::vector<base::string16>& result) {
    autofill_manager_->autocomplete_history_manager_->SendSuggestions(&result);
  }
