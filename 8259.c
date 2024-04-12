void ar6000_init_profile_info(struct ar6_softc *ar)
{
    ar->arSsidLen            = 0;
    A_MEMZERO(ar->arSsid, sizeof(ar->arSsid));

    switch(fwmode) {
        case HI_OPTION_FW_MODE_IBSS:
            ar->arNetworkType = ar->arNextMode = ADHOC_NETWORK;
            break;
        case HI_OPTION_FW_MODE_BSS_STA:
            ar->arNetworkType = ar->arNextMode = INFRA_NETWORK;
            break;
        case HI_OPTION_FW_MODE_AP:
            ar->arNetworkType = ar->arNextMode = AP_NETWORK;
            break;
    }

    ar->arDot11AuthMode      = OPEN_AUTH;
    ar->arAuthMode           = NONE_AUTH;
    ar->arPairwiseCrypto     = NONE_CRYPT;
    ar->arPairwiseCryptoLen  = 0;
    ar->arGroupCrypto        = NONE_CRYPT;
    ar->arGroupCryptoLen     = 0;
    A_MEMZERO(ar->arWepKeyList, sizeof(ar->arWepKeyList));
    A_MEMZERO(ar->arReqBssid, sizeof(ar->arReqBssid));
    A_MEMZERO(ar->arBssid, sizeof(ar->arBssid));
    ar->arBssChannel = 0;
}
