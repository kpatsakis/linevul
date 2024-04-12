NavigationState::NavigationState(
    const CommonNavigationParams& common_params,
    const CommitNavigationParams& commit_params,
    base::TimeTicks time_commit_requested,
    bool is_content_initiated,
    mojom::FrameNavigationControl::CommitNavigationCallback callback,
    mojom::NavigationClient::CommitNavigationCallback
        per_navigation_mojo_interface_commit_callback,
    std::unique_ptr<NavigationClient> navigation_client,
    bool was_initiated_in_this_frame)
    : request_committed_(false),
      was_within_same_document_(false),
      was_initiated_in_this_frame_(was_initiated_in_this_frame),
      is_content_initiated_(is_content_initiated),
      common_params_(common_params),
      commit_params_(commit_params),
      time_commit_requested_(time_commit_requested),
      navigation_client_(std::move(navigation_client)),
      commit_callback_(std::move(callback)),
      per_navigation_mojo_interface_commit_callback_(
          std::move(per_navigation_mojo_interface_commit_callback)) {}
