static inline pthread_t create_thread(void *(*start_routine)(void *), void * arg){
    APPL_TRACE_DEBUG("create_thread: entered");
 pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
 pthread_t thread_id = -1;
 if ( pthread_create(&thread_id, &thread_attr, start_routine, arg)!=0 )
 {
        APPL_TRACE_ERROR("pthread_create : %s", strerror(errno));
 return -1;
 }
    APPL_TRACE_DEBUG("create_thread: thread created successfully");
 return thread_id;
}
