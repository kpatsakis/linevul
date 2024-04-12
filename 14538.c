std::vector<uint8_t> GetTestAttestedCredentialDataBytes() {
  auto test_attested_data =
      fido_parsing_utils::Materialize(kTestAttestedCredentialDataPrefix);
  fido_parsing_utils::Append(&test_attested_data,
                             test_data::kTestECPublicKeyCOSE);
  return test_attested_data;
}
