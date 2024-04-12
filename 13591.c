string16 FormatViewSourceUrl(const GURL& url,
                             const std::vector<size_t>& original_offsets,
                             const std::string& languages,
                             FormatUrlTypes format_types,
                             UnescapeRule::Type unescape_rules,
                             url_parse::Parsed* new_parsed,
                             size_t* prefix_end,
                             std::vector<size_t>* offsets_for_adjustment) {
  DCHECK(new_parsed);
  const char kViewSource[] = "view-source:";
  const size_t kViewSourceLength = arraysize(kViewSource) - 1;
  std::vector<size_t> offsets_into_url(
      OffsetsIntoComponent(original_offsets, kViewSourceLength));

  GURL real_url(url.possibly_invalid_spec().substr(kViewSourceLength));
  string16 result(ASCIIToUTF16(kViewSource) +
      FormatUrlWithOffsets(real_url, languages, format_types, unescape_rules,
                           new_parsed, prefix_end, &offsets_into_url));

  if (new_parsed->scheme.is_nonempty()) {
    new_parsed->scheme.len += kViewSourceLength;
  } else {
    new_parsed->scheme.begin = 0;
    new_parsed->scheme.len = kViewSourceLength - 1;
  }
  AdjustComponents(kViewSourceLength, new_parsed);
  if (prefix_end)
    *prefix_end += kViewSourceLength;
  AdjustForComponentTransform(original_offsets, kViewSourceLength,
      url.possibly_invalid_spec().length(), offsets_into_url, kViewSourceLength,
      offsets_for_adjustment);
  LimitOffsets(result, offsets_for_adjustment);
  return result;
}
