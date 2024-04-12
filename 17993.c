void AudioHandler::Dispose() {
  DCHECK(IsMainThread());
  DCHECK(Context()->IsGraphOwner());

  Context()->GetDeferredTaskHandler().RemoveChangedChannelCountMode(this);
  Context()->GetDeferredTaskHandler().RemoveChangedChannelInterpretation(this);
  Context()->GetDeferredTaskHandler().RemoveAutomaticPullNode(this);
  for (auto& output : outputs_)
    output->Dispose();
  node_ = nullptr;
}
