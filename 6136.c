std::string TemplateURLRef::GetPostParamsString() const {
  switch (type_) {
    case INDEXED:
    case SEARCH:            return owner_->search_url_post_params();
    case SUGGEST:           return owner_->suggestions_url_post_params();
    case INSTANT:           return owner_->instant_url_post_params();
    case NEW_TAB:           return std::string();
    case CONTEXTUAL_SEARCH: return std::string();
    case IMAGE:             return owner_->image_url_post_params();
    default:      NOTREACHED(); return std::string();  // NOLINT
  }
}
