static rsRetVal validateConfig(instanceConf_t* info) {

    if (info->type == -1) {
        errmsg.LogError(0, RS_RET_INVALID_PARAMS,
                        "you entered an invalid type");
        return RS_RET_INVALID_PARAMS;
    }
    if (info->action == -1) {
        errmsg.LogError(0, RS_RET_INVALID_PARAMS,
                        "you entered an invalid action");
        return RS_RET_INVALID_PARAMS;
    }
    if (info->description == NULL) {
        errmsg.LogError(0, RS_RET_INVALID_PARAMS,
                        "you didn't enter a description");
        return RS_RET_INVALID_PARAMS;
    }
    if(info->type == ZMQ_SUB && info->subscriptions == NULL) {
        errmsg.LogError(0, RS_RET_INVALID_PARAMS,
                        "SUB sockets need a subscription");
        return RS_RET_INVALID_PARAMS;
    }
    if(info->type != ZMQ_SUB && info->subscriptions != NULL) {
        errmsg.LogError(0, RS_RET_INVALID_PARAMS,
                        "only SUB sockets can have subscriptions");
        return RS_RET_INVALID_PARAMS;
    }
    return RS_RET_OK;
}
