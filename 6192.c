  void UpdateControllerRole(unsigned int controller_index,
                            device::ControllerRole role) {
    auto controller_data = GetCurrentControllerData(controller_index);
    controller_data.role = role;
    UpdateControllerAndWait(controller_index, controller_data);
  }
