void Splay56To64(const uint8_t* key_56, uint8_t* key_64) {
  key_64[0] = key_56[0];
  key_64[1] = key_56[0] << 7 | key_56[1] >> 1;
  key_64[2] = key_56[1] << 6 | key_56[2] >> 2;
  key_64[3] = key_56[2] << 5 | key_56[3] >> 3;
  key_64[4] = key_56[3] << 4 | key_56[4] >> 4;
  key_64[5] = key_56[4] << 3 | key_56[5] >> 5;
  key_64[6] = key_56[5] << 2 | key_56[6] >> 6;
  key_64[7] = key_56[6] << 1;
}
