  void SetPermissionInfo(const PermissionInfoList& permission_info_list,
                         ChosenObjectInfoList chosen_object_info_list) {
    last_chosen_object_info_.clear();
    for (auto& chosen_object_info : chosen_object_info_list)
      last_chosen_object_info_.push_back(std::move(chosen_object_info));
    last_permission_info_list_ = permission_info_list;
  }
