void bdt_dut_mode_configure(char *p)
{
 int32_t mode = -1;

    bdt_log("BT DUT MODE CONFIGURE");
 if (!bt_enabled) {
        bdt_log("Bluetooth must be enabled for test_mode to work.");
 return;
 }
    mode = get_signed_int(&p, mode);
 if ((mode != 0) && (mode != 1)) {
        bdt_log("Please specify mode: 1 to enter, 0 to exit");
 return;
 }
    status = sBtInterface->dut_mode_configure(mode);

    check_return_status(status);
}
