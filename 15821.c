static int ScaleChannel(int channel, int volume) {
  return static_cast<int>((static_cast<Fixed>(channel) * volume) >> 16);
}
