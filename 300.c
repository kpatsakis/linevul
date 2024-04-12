MediaQueryMatcher& Document::GetMediaQueryMatcher() {
  if (!media_query_matcher_)
    media_query_matcher_ = MediaQueryMatcher::Create(*this);
  return *media_query_matcher_;
}
