void AudioHandler::PrintNodeCounts() {
  fprintf(stderr, "\n\n");
  fprintf(stderr, "===========================\n");
  fprintf(stderr, "AudioNode: reference counts\n");
  fprintf(stderr, "===========================\n");

  for (unsigned i = 0; i < kNodeTypeEnd; ++i)
    fprintf(stderr, "%2d: %d\n", i, node_count_[i]);

  fprintf(stderr, "===========================\n\n\n");
}
