void FillMiscNavigationParams(const CommonNavigationParams& common_params,
                              const CommitNavigationParams& commit_params,
                              blink::WebNavigationParams* navigation_params) {
  navigation_params->navigation_timings = BuildNavigationTimings(
      common_params.navigation_start, commit_params.navigation_timing,
      common_params.input_start);

  navigation_params->is_user_activated =
      commit_params.was_activated == WasActivatedOption::kYes;

  if (commit_params.origin_to_commit) {
    navigation_params->origin_to_commit =
        commit_params.origin_to_commit.value();
  }
}
