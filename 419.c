TopDomainEntry IDNSpoofChecker::LookupSkeletonInTopDomains(
    const std::string& skeleton) {
  DCHECK(!skeleton.empty());
  TopDomainPreloadDecoder preload_decoder(
      g_trie_params.huffman_tree, g_trie_params.huffman_tree_size,
      g_trie_params.trie, g_trie_params.trie_bits,
      g_trie_params.trie_root_position);
  auto labels = base::SplitStringPiece(skeleton, ".", base::KEEP_WHITESPACE,
                                       base::SPLIT_WANT_ALL);

  if (labels.size() > kNumberOfLabelsToCheck) {
    labels.erase(labels.begin(),
                 labels.begin() + labels.size() - kNumberOfLabelsToCheck);
  }

  while (labels.size() > 1) {
    std::string partial_skeleton = base::JoinString(labels, ".");
    bool match = false;
    bool decoded = preload_decoder.Decode(partial_skeleton, &match);
    DCHECK(decoded);
    if (!decoded)
      return TopDomainEntry();

    if (match)
      return preload_decoder.matching_top_domain();

    labels.erase(labels.begin());
  }
  return TopDomainEntry();
}
