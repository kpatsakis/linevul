void HTMLLinkElement::ParseAttribute(
    const AttributeModificationParams& params) {
  const QualifiedName& name = params.name;
  const AtomicString& value = params.new_value;
  if (name == relAttr) {
    rel_attribute_ = LinkRelAttribute(value);
    if (rel_attribute_.IsImport()) {
      Deprecation::CountDeprecation(GetDocument(), WebFeature::kHTMLImports);
    }
    rel_list_->DidUpdateAttributeValue(params.old_value, value);
    Process();
  } else if (name == hrefAttr) {
    LogUpdateAttributeIfIsolatedWorldAndInDocument("link", params);
    Process();
  } else if (name == typeAttr) {
    type_ = value;
    Process();
  } else if (name == asAttr) {
    as_ = value;
    Process();
  } else if (name == referrerpolicyAttr) {
    if (!value.IsNull()) {
      SecurityPolicy::ReferrerPolicyFromString(
          value, kDoNotSupportReferrerPolicyLegacyKeywords, &referrer_policy_);
      UseCounter::Count(GetDocument(),
                        WebFeature::kHTMLLinkElementReferrerPolicyAttribute);
    }
  } else if (name == sizesAttr) {
    sizes_->DidUpdateAttributeValue(params.old_value, value);
    WebVector<WebSize> web_icon_sizes =
        WebIconSizesParser::ParseIconSizes(value);
    icon_sizes_.resize(SafeCast<wtf_size_t>(web_icon_sizes.size()));
    for (wtf_size_t i = 0; i < icon_sizes_.size(); ++i)
      icon_sizes_[i] = web_icon_sizes[i];
    Process();
  } else if (name == mediaAttr) {
    media_ = value.DeprecatedLower();
    Process();
  } else if (name == scopeAttr) {
    scope_ = value;
    Process();
  } else if (name == integrityAttr) {
    integrity_ = value;
  } else if (name == importanceAttr &&
             RuntimeEnabledFeatures::PriorityHintsEnabled()) {
    importance_ = value;
  } else if (name == disabledAttr) {
    UseCounter::Count(GetDocument(), WebFeature::kHTMLLinkElementDisabled);
    if (params.reason == AttributeModificationReason::kByParser)
      UseCounter::Count(GetDocument(), WebFeature::kHTMLLinkElementDisabledByParser);
    if (LinkStyle* link = GetLinkStyle())
      link->SetDisabledState(!value.IsNull());
  } else {
    if (name == titleAttr) {
      if (LinkStyle* link = GetLinkStyle())
        link->SetSheetTitle(value);
    }

    HTMLElement::ParseAttribute(params);
  }
}
