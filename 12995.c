static BOOLEAN btif_hl_get_bta_mdep_role(bthl_mdep_role_t mdep, tBTA_HL_MDEP_ROLE *p){
    BOOLEAN status = TRUE;
 switch (mdep)
 {
 case BTHL_MDEP_ROLE_SOURCE:
 *p = BTA_HL_MDEP_ROLE_SOURCE;
 break;
 case BTHL_MDEP_ROLE_SINK:
 *p = BTA_HL_MDEP_ROLE_SINK;
 break;
 default:
 *p = BTA_HL_MDEP_ROLE_SOURCE;
            status = FALSE;
 break;
 }

    BTIF_TRACE_DEBUG("%s status=%d bta_mdep_role=%d (%d:btif)",
                      __FUNCTION__, status, *p, mdep);
 return status;
}
