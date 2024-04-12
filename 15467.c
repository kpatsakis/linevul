void EglRenderingVDAClient::NotifyInitializeDone() {
  SetState(CS_INITIALIZED);
  initialize_done_ticks_ = base::TimeTicks::Now();
  for (int i = 0; i < num_in_flight_decodes_; ++i)
    DecodeNextNALUs();
}
