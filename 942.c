void FlagsState::SetExperimentEnabled(FlagsStorage* flags_storage,
                                      const std::string& internal_name,
                                      bool enable) {
  size_t at_index = internal_name.find(testing::kMultiSeparator);
  if (at_index != std::string::npos) {
    DCHECK(enable);
    DCHECK_NE(at_index, 0u);
    const std::string experiment_name = internal_name.substr(0, at_index);
    SetExperimentEnabled(flags_storage, experiment_name, false);

    if (internal_name != experiment_name + "@0") {
      std::set<std::string> enabled_experiments;
      GetSanitizedEnabledFlags(flags_storage, &enabled_experiments);
      needs_restart_ |= enabled_experiments.insert(internal_name).second;
      flags_storage->SetFlags(enabled_experiments);
    }
    return;
  }

  std::set<std::string> enabled_experiments;
  GetSanitizedEnabledFlags(flags_storage, &enabled_experiments);

  const Experiment* e = NULL;
  for (size_t i = 0; i < num_experiments; ++i) {
    if (experiments[i].internal_name == internal_name) {
      e = experiments + i;
      break;
    }
  }
  DCHECK(e);

  if (e->type == Experiment::SINGLE_VALUE) {
    if (enable)
      needs_restart_ |= enabled_experiments.insert(internal_name).second;
    else
      needs_restart_ |= (enabled_experiments.erase(internal_name) > 0);
  } else {
    if (enable) {
      needs_restart_ |= enabled_experiments.insert(e->NameForChoice(0)).second;
    } else {
      for (int i = 0; i < e->num_choices; ++i) {
        std::string choice_name = e->NameForChoice(i);
        if (enabled_experiments.find(choice_name) !=
            enabled_experiments.end()) {
          needs_restart_ = true;
          enabled_experiments.erase(choice_name);
        }
      }
    }
  }

  flags_storage->SetFlags(enabled_experiments);
}
