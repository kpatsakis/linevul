void FlagsState::ConvertFlagsToSwitches(
    PrefService* prefs, CommandLine* command_line) {
  if (command_line->HasSwitch(switches::kNoExperiments))
    return;

  std::set<std::string> enabled_experiments;

  GetSanitizedEnabledFlagsForCurrentPlatform(prefs, &enabled_experiments);

  typedef std::map<std::string, std::pair<std::string, std::string> >
      NameToSwitchAndValueMap;
  NameToSwitchAndValueMap name_to_switch_map;
  for (size_t i = 0; i < num_experiments; ++i) {
    const Experiment& e = experiments[i];
    if (e.type == Experiment::SINGLE_VALUE) {
      name_to_switch_map[e.internal_name] =
          std::pair<std::string, std::string>(e.command_line_switch,
                                              e.command_line_value);
    } else {
      for (int j = 0; j < e.num_choices; ++j)
        name_to_switch_map[NameForChoice(e, j)] =
            std::pair<std::string, std::string>(
                e.choices[j].command_line_switch,
                e.choices[j].command_line_value);
    }
  }

  command_line->AppendSwitch(switches::kFlagSwitchesBegin);
  flags_switches_.insert(
      std::pair<std::string, std::string>(switches::kFlagSwitchesBegin,
                                          std::string()));
  for (std::set<std::string>::iterator it = enabled_experiments.begin();
       it != enabled_experiments.end();
       ++it) {
    const std::string& experiment_name = *it;
    NameToSwitchAndValueMap::const_iterator name_to_switch_it =
        name_to_switch_map.find(experiment_name);
    if (name_to_switch_it == name_to_switch_map.end()) {
      NOTREACHED();
      continue;
    }

    const std::pair<std::string, std::string>&
        switch_and_value_pair = name_to_switch_it->second;

    command_line->AppendSwitchASCII(switch_and_value_pair.first,
                                    switch_and_value_pair.second);
    flags_switches_[switch_and_value_pair.first] = switch_and_value_pair.second;
  }
  command_line->AppendSwitch(switches::kFlagSwitchesEnd);
  flags_switches_.insert(
      std::pair<std::string, std::string>(switches::kFlagSwitchesEnd,
                                          std::string()));
}
