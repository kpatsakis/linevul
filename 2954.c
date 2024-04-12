bool venc_dev::venc_set_voptiming_cfg( OMX_U32 TimeIncRes)
{

 struct venc_voptimingcfg vop_timing_cfg;

    DEBUG_PRINT_LOW("venc_set_voptiming_cfg: TimeRes = %u",
 (unsigned int)TimeIncRes);

    vop_timing_cfg.voptime_resolution = TimeIncRes;

    voptimecfg.voptime_resolution = vop_timing_cfg.voptime_resolution;
 return true;
}
