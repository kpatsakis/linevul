bool MdPolicyPageEnabled() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(
      ::switches::kEnableMaterialDesignPolicyPage);
}
