static bool ValidMpegAudioFrameHeader(const uint8* header,
                                      int header_size,
                                      int* framesize) {
  DCHECK_GE(header_size, 4);
  *framesize = 0;
  BitReader reader(header, 4);  // Header can only be 4 bytes long.

  RCHECK(ReadBits(&reader, 11) == 0x7ff);

  int version = ReadBits(&reader, 2);
  RCHECK(version != 1);  // Reserved.

  int layer = ReadBits(&reader, 2);
  RCHECK(layer != 0);

  reader.SkipBits(1);

  int bitrate_index = ReadBits(&reader, 4);
  RCHECK(bitrate_index != 0xf);

  int sampling_index = ReadBits(&reader, 2);
  RCHECK(sampling_index != 3);

  int padding = ReadBits(&reader, 1);

  int sampling_rate = kSampleRateTable[version][sampling_index];
  int bitrate;
  if (version == VERSION_1) {
    if (layer == LAYER_1)
      bitrate = kBitRateTableV1L1[bitrate_index];
    else if (layer == LAYER_2)
      bitrate = kBitRateTableV1L2[bitrate_index];
    else
      bitrate = kBitRateTableV1L3[bitrate_index];
  } else {
    if (layer == LAYER_1)
      bitrate = kBitRateTableV2L1[bitrate_index];
    else
      bitrate = kBitRateTableV2L23[bitrate_index];
  }
  if (layer == LAYER_1)
    *framesize = ((12000 * bitrate) / sampling_rate + padding) * 4;
  else
    *framesize = (144000 * bitrate) / sampling_rate + padding;
  return (bitrate > 0 && sampling_rate > 0);
}
