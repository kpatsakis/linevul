void FlagsState::RemoveFlagsSwitches(
    std::map<std::string, base::CommandLine::StringType>* switch_list) {
  for (const auto& entry : flags_switches_)
    switch_list->erase(entry.first);
}
