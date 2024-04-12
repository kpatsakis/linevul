variations::Study_Channel GetChannelForVariations() {
  switch (chrome::GetChannel()) {
    case version_info::Channel::CANARY:
      return variations::Study_Channel_CANARY;
    case version_info::Channel::DEV:
      return variations::Study_Channel_DEV;
    case version_info::Channel::BETA:
      return variations::Study_Channel_BETA;
    case version_info::Channel::STABLE:
      return variations::Study_Channel_STABLE;
    case version_info::Channel::UNKNOWN:
      break;
  }
  const std::string forced_channel =
      base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
          switches::kFakeVariationsChannel);
  if (forced_channel == "stable")
    return variations::Study_Channel_STABLE;
  if (forced_channel == "beta")
    return variations::Study_Channel_BETA;
  if (forced_channel == "dev")
    return variations::Study_Channel_DEV;
  if (forced_channel == "canary")
    return variations::Study_Channel_CANARY;
  DVLOG(1) << "Invalid channel provided: " << forced_channel;
  return variations::Study_Channel_UNKNOWN;
}
