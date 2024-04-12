bt_status_t btif_hh_execute_service(BOOLEAN b_enable)
{
 if (b_enable)
 {
 /* Enable and register with BTA-HH */
          BTA_HhEnable(BTUI_HH_SECURITY, bte_hh_evt);
 }
 else {
 /* Disable HH */
         BTA_HhDisable();
 }
 return BT_STATUS_SUCCESS;
}
