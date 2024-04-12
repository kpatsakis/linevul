bool WriteResponsePayloadsV2(
    NtlmBufferWriter* authenticate_writer,
    base::span<const uint8_t, kResponseLenV1> lm_response,
    base::span<const uint8_t, kNtlmProofLenV2> v2_proof,
    base::span<const uint8_t> v2_proof_input,
    base::span<const uint8_t> updated_target_info) {
  return authenticate_writer->WriteBytes(lm_response) &&
         authenticate_writer->WriteBytes(v2_proof) &&
         authenticate_writer->WriteBytes(v2_proof_input) &&
         authenticate_writer->WriteBytes(updated_target_info) &&
         authenticate_writer->WriteUInt32(0);
}
