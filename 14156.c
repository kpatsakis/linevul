void ProfileSyncService::GetDataTypeControllerStates(
  browser_sync::DataTypeController::StateMap* state_map) const {
    for (browser_sync::DataTypeController::TypeMap::const_iterator iter =
         data_type_controllers_.begin(); iter != data_type_controllers_.end();
         ++iter)
      (*state_map)[iter->first] = iter->second.get()->state();
}
