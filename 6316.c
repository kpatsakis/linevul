DefaultAudioDestinationNode* DefaultAudioDestinationNode::Create(
    BaseAudioContext* context,
    const WebAudioLatencyHint& latency_hint) {
  return MakeGarbageCollected<DefaultAudioDestinationNode>(*context,
                                                           latency_hint);
}
