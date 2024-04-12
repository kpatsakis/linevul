void SyncBackendHost::FinishConfigureDataTypesOnFrontendLoop() {
  DCHECK_EQ(MessageLoop::current(), frontend_loop_);

  SDVLOG(1) << "Syncer in config mode. SBH executing "
            << "FinishConfigureDataTypesOnFrontendLoop";


  ModelSafeRoutingInfo routing_info;
  registrar_->GetModelSafeRoutingInfo(&routing_info);
  const syncable::ModelTypeSet enabled_types =
      GetRoutingInfoTypes(routing_info);

  chrome_sync_notification_bridge_.UpdateEnabledTypes(enabled_types);

  if (pending_config_mode_state_->added_types.Empty() &&
      !core_->sync_manager()->InitialSyncEndedForAllEnabledTypes()) {

    pending_config_mode_state_->added_types =
        sync_api::GetTypesWithEmptyProgressMarkerToken(enabled_types,
                                                       GetUserShare());
  }

  if (pending_config_mode_state_->added_types.Empty()) {
    SDVLOG(1) << "No new types added; calling ready_task directly";
    const syncable::ModelTypeSet failed_configuration_types;
    pending_config_mode_state_->ready_task.Run(failed_configuration_types);
  } else {
    pending_download_state_.reset(pending_config_mode_state_.release());

    syncable::ModelTypeSet types_to_config =
        pending_download_state_->added_types;
    if (IsNigoriEnabled()) {
      types_to_config.Put(syncable::NIGORI);
    }
    SDVLOG(1) << "Types "
              << syncable::ModelTypeSetToString(types_to_config)
              << " added; calling DoRequestConfig";
    sync_thread_.message_loop()->PostTask(FROM_HERE,
         base::Bind(&SyncBackendHost::Core::DoRequestConfig,
                    core_.get(),
                    types_to_config,
                    pending_download_state_->reason));
  }

  pending_config_mode_state_.reset();

  sync_thread_.message_loop()->PostTask(FROM_HERE,
      base::Bind(&SyncBackendHost::Core::DoUpdateEnabledTypes, core_.get()));
}
