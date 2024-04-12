Policy* Document::policy() {
  if (!policy_)
    policy_ = new DocumentPolicy(this);
  return policy_.Get();
}
