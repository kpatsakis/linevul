int PreProc_Init() {
 size_t i;
 int status = 0;

 if (sInitStatus <= 0) {
 return sInitStatus;
 }
 for (i = 0; i < PREPROC_NUM_SESSIONS && status == 0; i++) {
        status = Session_Init(&sSessions[i]);
 }
    sInitStatus = status;
 return sInitStatus;
}
