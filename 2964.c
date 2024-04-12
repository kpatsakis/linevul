void CSSStyleSheet::SetText(const String& text) {
  child_rule_cssom_wrappers_.clear();

  CSSStyleSheet::RuleMutationScope mutation_scope(this);
  contents_->ClearRules();
  contents_->ParseString(text);
}
