static int lib_init()
{
    pthread_once(&once, init_once);
    ALOGV("%s Called ", __func__);
 return init_status;
}
