void GenerateResponseDesl(base::span<const uint8_t, kNtlmHashLen> hash,
                          base::span<const uint8_t, kChallengeLen> challenge,
                          base::span<uint8_t, kResponseLenV1> response) {
  constexpr size_t block_count = 3;
  constexpr size_t block_size = sizeof(DES_cblock);
  static_assert(kChallengeLen == block_size,
                "kChallengeLen must equal block_size");
  static_assert(kResponseLenV1 == block_count * block_size,
                "kResponseLenV1 must equal block_count * block_size");

  const DES_cblock* challenge_block =
      reinterpret_cast<const DES_cblock*>(challenge.data());
  uint8_t keys[block_count * block_size];

  Create3DesKeysFromNtlmHash(hash, keys);
  for (size_t ix = 0; ix < block_count * block_size; ix += block_size) {
    DES_cblock* key_block = reinterpret_cast<DES_cblock*>(keys + ix);
    DES_cblock* response_block =
        reinterpret_cast<DES_cblock*>(response.data() + ix);

    DES_key_schedule key_schedule;
    DES_set_odd_parity(key_block);
    DES_set_key(key_block, &key_schedule);
    DES_ecb_encrypt(challenge_block, response_block, &key_schedule,
                    DES_ENCRYPT);
  }
}
