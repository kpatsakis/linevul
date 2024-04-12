void SimpleSoftOMXComponent::onSendCommand(
        OMX_COMMANDTYPE cmd, OMX_U32 param) {
 switch (cmd) {
 case OMX_CommandStateSet:
 {
            onChangeState((OMX_STATETYPE)param);
 break;
 }

 case OMX_CommandPortEnable:
 case OMX_CommandPortDisable:
 {
            onPortEnable(param, cmd == OMX_CommandPortEnable);
 break;
 }

 case OMX_CommandFlush:
 {
            onPortFlush(param, true /* sendFlushComplete */);
 break;
 }

 default:
            TRESPASS();
 break;
 }
}
