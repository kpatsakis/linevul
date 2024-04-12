LastEventTimeToggleResetAll(Bool state)
{
    DeviceIntPtr dev;
    nt_list_for_each_entry(dev, inputInfo.devices, next) {
        LastEventTimeToggleResetFlag(dev->id, FALSE);
    }
    LastEventTimeToggleResetFlag(XIAllDevices, FALSE);
    LastEventTimeToggleResetFlag(XIAllMasterDevices, FALSE);
}
