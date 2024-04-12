bool checkDigest(const String& source,
                 ContentSecurityPolicy::InlineType type,
                 uint8_t hashAlgorithmsUsed,
                 const CSPDirectiveListVector& policies) {
  static const struct {
    ContentSecurityPolicyHashAlgorithm cspHashAlgorithm;
    HashAlgorithm algorithm;
  } kAlgorithmMap[] = {
      {ContentSecurityPolicyHashAlgorithmSha1, HashAlgorithmSha1},
      {ContentSecurityPolicyHashAlgorithmSha256, HashAlgorithmSha256},
      {ContentSecurityPolicyHashAlgorithmSha384, HashAlgorithmSha384},
      {ContentSecurityPolicyHashAlgorithmSha512, HashAlgorithmSha512}};

  if (hashAlgorithmsUsed == ContentSecurityPolicyHashAlgorithmNone)
    return false;

  StringUTF8Adaptor utf8Source(source);

  for (const auto& algorithmMap : kAlgorithmMap) {
    DigestValue digest;
    if (algorithmMap.cspHashAlgorithm & hashAlgorithmsUsed) {
      bool digestSuccess =
          computeDigest(algorithmMap.algorithm, utf8Source.data(),
                        utf8Source.length(), digest);
      if (digestSuccess &&
          isAllowedByAll<allowed>(
              policies, CSPHashValue(algorithmMap.cspHashAlgorithm, digest),
              type))
        return true;
    }
  }

  return false;
}
