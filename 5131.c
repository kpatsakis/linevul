  const ContentSuggestion* GetSuggestionToNotifyAbout(Category category) {
    const auto& suggestions = service_->GetSuggestionsForCategory(category);
    if (variations::GetVariationParamByFeatureAsBool(
             kContentSuggestionsNotificationsFeature,
             kContentSuggestionsNotificationsAlwaysNotifyParam, false)) {
      if (category.IsKnownCategory(KnownCategories::ARTICLES) &&
          !suggestions.empty()) {
        return &suggestions[0];
      }
      return nullptr;
    }

    for (const ContentSuggestion& suggestion : suggestions) {
      if (suggestion.notification_extra()) {
        return &suggestion;
      }
    }
    return nullptr;
  }
