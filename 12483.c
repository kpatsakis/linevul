static rsRetVal createListener(struct cnfparamvals* pvals) {
    instanceConf_t* inst;
    int i;
    DEFiRet;
    
    CHKiRet(createInstance(&inst));
    for(i = 0 ; i < inppblk.nParams ; ++i) {
        if(!pvals[i].bUsed) 
            continue;	
        if(!strcmp(inppblk.descr[i].name, "ruleset")) {
            inst->pszBindRuleset = (uchar *)es_str2cstr(pvals[i].val.d.estr, NULL);
        } else if(!strcmp(inppblk.descr[i].name, "description")) {
            inst->description = es_str2cstr(pvals[i].val.d.estr, NULL);
        } else if(!strcmp(inppblk.descr[i].name, "sockType")){
            inst->type = getSocketType(es_str2cstr(pvals[i].val.d.estr, NULL));
        } else if(!strcmp(inppblk.descr[i].name, "action")){
            inst->action = getSocketAction(es_str2cstr(pvals[i].val.d.estr, NULL));
        } else if(!strcmp(inppblk.descr[i].name, "sndHWM")) {
            inst->sndHWM = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "rcvHWM")) {
            inst->rcvHWM = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "subscribe")) {
            char *subscribes = es_str2cstr(pvals[i].val.d.estr, NULL);
            rsRetVal ret = parseSubscriptions(subscribes, &inst->subscriptions);
            free(subscribes);
            CHKiRet(ret);
        } else if(!strcmp(inppblk.descr[i].name, "identity")){
            inst->identity = es_str2cstr(pvals[i].val.d.estr, NULL);
        } else if(!strcmp(inppblk.descr[i].name, "sndBuf")) {
            inst->sndBuf = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "rcvBuf")) {
            inst->rcvBuf = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "linger")) {
            inst->linger = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "backlog")) {
            inst->backlog = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "sndTimeout")) {
            inst->sndTimeout = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "rcvTimeout")) {
            inst->rcvTimeout = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "maxMsgSize")) {
            inst->maxMsgSize = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "rate")) {
            inst->rate = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "recoveryIVL")) {
            inst->recoveryIVL = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "multicastHops")) {
            inst->multicastHops = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "reconnectIVL")) {
            inst->reconnectIVL = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "reconnectIVLMax")) {
            inst->reconnectIVLMax = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "ipv4Only")) {
            inst->ipv4Only = (int) pvals[i].val.d.n;
        } else if(!strcmp(inppblk.descr[i].name, "affinity")) {
            inst->affinity = (int) pvals[i].val.d.n;
        } else {
            errmsg.LogError(0, NO_ERRCODE, "imzmq3: program error, non-handled "
                            "param '%s'\n", inppblk.descr[i].name);
        }
    
    }
finalize_it:
    RETiRet;
}
