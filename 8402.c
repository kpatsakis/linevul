ParseCertificatePrincipalPattern(const base::Value* pattern) {
  return certificate_matching::CertificatePrincipalPattern::
      ParseFromOptionalDict(pattern, "CN", "L", "O", "OU");
}
