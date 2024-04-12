int Effect_SetState(preproc_effect_t *effect, uint32_t state)
{
 int status = 0;
    ALOGV("Effect_SetState proc %d, new %d old %d", effect->procId, state, effect->state);
 switch(state) {
 case PREPROC_EFFECT_STATE_INIT:
 switch(effect->state) {
 case PREPROC_EFFECT_STATE_ACTIVE:
            effect->ops->disable(effect);
 Session_SetProcEnabled(effect->session, effect->procId, false);
 case PREPROC_EFFECT_STATE_CONFIG:
 case PREPROC_EFFECT_STATE_CREATED:
 case PREPROC_EFFECT_STATE_INIT:
 break;
 default:
            BAD_STATE_ABORT(effect->state, state);
 }
 break;
 case PREPROC_EFFECT_STATE_CREATED:
 switch(effect->state) {
 case PREPROC_EFFECT_STATE_INIT:
            status = effect->ops->create(effect);
 break;
 case PREPROC_EFFECT_STATE_CREATED:
 case PREPROC_EFFECT_STATE_ACTIVE:
 case PREPROC_EFFECT_STATE_CONFIG:
            ALOGE("Effect_SetState invalid transition");
            status = -ENOSYS;
 break;
 default:
            BAD_STATE_ABORT(effect->state, state);
 }
 break;
 case PREPROC_EFFECT_STATE_CONFIG:
 switch(effect->state) {
 case PREPROC_EFFECT_STATE_INIT:
            ALOGE("Effect_SetState invalid transition");
            status = -ENOSYS;
 break;
 case PREPROC_EFFECT_STATE_ACTIVE:
            effect->ops->disable(effect);
 Session_SetProcEnabled(effect->session, effect->procId, false);
 break;
 case PREPROC_EFFECT_STATE_CREATED:
 case PREPROC_EFFECT_STATE_CONFIG:
 break;
 default:
            BAD_STATE_ABORT(effect->state, state);
 }
 break;
 case PREPROC_EFFECT_STATE_ACTIVE:
 switch(effect->state) {
 case PREPROC_EFFECT_STATE_INIT:
 case PREPROC_EFFECT_STATE_CREATED:
            ALOGE("Effect_SetState invalid transition");
            status = -ENOSYS;
 break;
 case PREPROC_EFFECT_STATE_ACTIVE:
 break;
 case PREPROC_EFFECT_STATE_CONFIG:
            effect->ops->enable(effect);
 Session_SetProcEnabled(effect->session, effect->procId, true);
 break;
 default:
            BAD_STATE_ABORT(effect->state, state);
 }
 break;
 default:
        BAD_STATE_ABORT(effect->state, state);
 }
 if (status == 0) {
        effect->state = state;
 }
 return status;
}
