string16 BuildSnippet(const std::string& document,
                      const std::string& query) {
  const std::string document_folded = StringToLowerASCII(std::string(document));

  std::vector<std::string> query_words;
  SplitString(query, ' ', &query_words);

  Snippet::MatchPositions match_positions;
  match_positions.clear();
  for (std::vector<std::string>::iterator qw = query_words.begin();
       qw != query_words.end(); ++qw) {
    size_t ofs = 0;
    while ((ofs = document_folded.find(*qw, ofs)) != std::string::npos) {
      match_positions.push_back(std::make_pair(ofs, ofs + qw->size()));
      ofs += qw->size();
    }
  }
  std::sort(match_positions.begin(), match_positions.end(), ComparePair1st);

  Snippet snippet;
  snippet.ComputeSnippet(match_positions, document);

  string16 star_snippet;
  Snippet::MatchPositions::const_iterator match;
  size_t pos = 0;
  for (match = snippet.matches().begin();
       match != snippet.matches().end(); ++match) {
    star_snippet += snippet.text().substr(pos, match->first - pos);
    star_snippet += UTF8ToUTF16("**");
    star_snippet += snippet.text().substr(match->first,
                                          match->second - match->first);
    star_snippet += UTF8ToUTF16("**");
    pos = match->second;
  }
  star_snippet += snippet.text().substr(pos);

  return star_snippet;
}
