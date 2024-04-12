void btif_dm_read_energy_info()
{
#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
    BTA_DmBleGetEnergyInfo(bta_energy_info_cb);
#endif
}
