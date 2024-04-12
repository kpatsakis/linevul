void FlagsState::ConvertFlagsToSwitches(FlagsStorage* flags_storage,
                                        base::CommandLine* command_line,
                                        SentinelsMode sentinels) {
  if (command_line->HasSwitch(switches::kNoExperiments))
    return;

  std::set<std::string> enabled_experiments;

  GetSanitizedEnabledFlagsForCurrentPlatform(flags_storage,
                                             &enabled_experiments);

  NameToSwitchAndValueMap name_to_switch_map;
  for (size_t i = 0; i < num_experiments; ++i) {
    const Experiment& e = experiments[i];
    if (e.type == Experiment::SINGLE_VALUE) {
      SetFlagToSwitchMapping(e.internal_name, e.command_line_switch,
                             e.command_line_value, &name_to_switch_map);
    } else if (e.type == Experiment::MULTI_VALUE) {
      for (int j = 0; j < e.num_choices; ++j) {
        SetFlagToSwitchMapping(e.NameForChoice(j),
                               e.choices[j].command_line_switch,
                               e.choices[j].command_line_value,
                               &name_to_switch_map);
      }
    } else {
      DCHECK_EQ(e.type, Experiment::ENABLE_DISABLE_VALUE);
      SetFlagToSwitchMapping(e.NameForChoice(0), std::string(), std::string(),
                             &name_to_switch_map);
      SetFlagToSwitchMapping(e.NameForChoice(1), e.command_line_switch,
                             e.command_line_value, &name_to_switch_map);
      SetFlagToSwitchMapping(e.NameForChoice(2), e.disable_command_line_switch,
                             e.disable_command_line_value, &name_to_switch_map);
    }
  }

  if (sentinels == kAddSentinels) {
    command_line->AppendSwitch(switches::kFlagSwitchesBegin);
    flags_switches_.insert(
        std::pair<std::string, std::string>(switches::kFlagSwitchesBegin,
                                            std::string()));
  }
  for (const std::string& experiment_name : enabled_experiments) {
    NameToSwitchAndValueMap::const_iterator name_to_switch_it =
        name_to_switch_map.find(experiment_name);
    if (name_to_switch_it == name_to_switch_map.end()) {
      NOTREACHED();
      continue;
    }

    const std::pair<std::string, std::string>&
        switch_and_value_pair = name_to_switch_it->second;

    CHECK(!switch_and_value_pair.first.empty());
    command_line->AppendSwitchASCII(switch_and_value_pair.first,
                                    switch_and_value_pair.second);
    flags_switches_[switch_and_value_pair.first] = switch_and_value_pair.second;
  }
  if (sentinels == kAddSentinels) {
    command_line->AppendSwitch(switches::kFlagSwitchesEnd);
    flags_switches_.insert(
        std::pair<std::string, std::string>(switches::kFlagSwitchesEnd,
                                            std::string()));
  }
}
