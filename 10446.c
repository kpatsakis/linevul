void AudioHandler::CheckNumberOfChannelsForInput(AudioNodeInput* input) {
  DCHECK(Context()->IsAudioThread());
  DCHECK(Context()->IsGraphOwner());

  DCHECK(inputs_.Contains(input));
  if (!inputs_.Contains(input))
    return;

  input->UpdateInternalBus();
}
