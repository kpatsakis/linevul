ar6000_ap_mode_profile_commit(struct ar6_softc *ar)
{
    WMI_CONNECT_CMD p;
    unsigned long  flags;

    /* No change in AP's profile configuration */
    if(ar->ap_profile_flag==0) {
        A_PRINTF("COMMIT: No change in profile!!!\n");
        return -ENODATA;
    }

    if(!ar->arSsidLen) {
        A_PRINTF("SSID not set!!!\n");
        return -ECHRNG;
    }

    switch(ar->arAuthMode) {
    case NONE_AUTH:
        if((ar->arPairwiseCrypto != NONE_CRYPT) &&
#ifdef WAPI_ENABLE
           (ar->arPairwiseCrypto != WAPI_CRYPT) &&
#endif
           (ar->arPairwiseCrypto != WEP_CRYPT)) {
            A_PRINTF("Cipher not supported in AP mode Open auth\n");
            return -EOPNOTSUPP;
        }
        break;
    case WPA_PSK_AUTH:
    case WPA2_PSK_AUTH:
    case (WPA_PSK_AUTH|WPA2_PSK_AUTH):
        break;
    default:
        A_PRINTF("This key mgmt type not supported in AP mode\n");
        return -EOPNOTSUPP;
    }

    /* Update the arNetworkType */
    ar->arNetworkType = ar->arNextMode;

    A_MEMZERO(&p,sizeof(p));
    p.ssidLength = ar->arSsidLen;
    memcpy(p.ssid,ar->arSsid,p.ssidLength);
    p.channel = ar->arChannelHint;
    p.networkType = ar->arNetworkType;

    p.dot11AuthMode = ar->arDot11AuthMode;
    p.authMode = ar->arAuthMode;
    p.pairwiseCryptoType = ar->arPairwiseCrypto;
    p.pairwiseCryptoLen = ar->arPairwiseCryptoLen;
    p.groupCryptoType = ar->arGroupCrypto;
    p.groupCryptoLen = ar->arGroupCryptoLen;
    p.ctrl_flags = ar->arConnectCtrlFlags;

    wmi_ap_profile_commit(ar->arWmi, &p);
    spin_lock_irqsave(&ar->arLock, flags);
    ar->arConnected  = true;
    netif_carrier_on(ar->arNetDev);
    spin_unlock_irqrestore(&ar->arLock, flags);
    ar->ap_profile_flag = 0;
    return 0;
}
