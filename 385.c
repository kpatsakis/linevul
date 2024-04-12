int BassBoost_getParameter(EffectContext *pContext,
 void *pParam,
 uint32_t *pValueSize,
 void *pValue){
 int status = 0;
 int32_t *pParamTemp = (int32_t *)pParam;
 int32_t param = *pParamTemp++;
 int32_t param2;
 char *name;


 switch (param){
 case BASSBOOST_PARAM_STRENGTH_SUPPORTED:
 if (*pValueSize != sizeof(uint32_t)){
                ALOGV("\tLVM_ERROR : BassBoost_getParameter() invalid pValueSize1 %d", *pValueSize);
 return -EINVAL;
 }
 *pValueSize = sizeof(uint32_t);
 break;
 case BASSBOOST_PARAM_STRENGTH:
 if (*pValueSize != sizeof(int16_t)){
                ALOGV("\tLVM_ERROR : BassBoost_getParameter() invalid pValueSize2 %d", *pValueSize);
 return -EINVAL;
 }
 *pValueSize = sizeof(int16_t);
 break;

 default:
            ALOGV("\tLVM_ERROR : BassBoost_getParameter() invalid param %d", param);
 return -EINVAL;
 }

 switch (param){
 case BASSBOOST_PARAM_STRENGTH_SUPPORTED:
 *(uint32_t *)pValue = 1;

 break;

 case BASSBOOST_PARAM_STRENGTH:
 *(int16_t *)pValue = BassGetStrength(pContext);

 break;

 default:
            ALOGV("\tLVM_ERROR : BassBoost_getParameter() invalid param %d", param);
            status = -EINVAL;
 break;
 }

 return status;
} /* end BassBoost_getParameter */
