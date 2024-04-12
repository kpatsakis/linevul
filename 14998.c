bool LeafUnwindBlacklist::IsBlacklisted(const void* module) const {
   return ContainsKey(blacklisted_modules_, module);
 }
