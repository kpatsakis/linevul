void AddPluginDllEvictionPolicy(sandbox::TargetPolicy* policy) {
  for (int ix = 0; ix != arraysize(kTroublesomePluginDlls); ++ix)
    BlacklistAddOneDll(kTroublesomePluginDlls[ix], false, policy);
}
