void AudioHandler::UpdateChannelsForInputs() {
  for (auto& input : inputs_)
    input->ChangedOutputs();
}
