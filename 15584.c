static THREAD_FUNCTION thread_decoding_proc(void *p_data)
{
 int ithread = ((DECODETHREAD_DATA *)p_data)->ithread;
    VP8D_COMP *pbi = (VP8D_COMP *)(((DECODETHREAD_DATA *)p_data)->ptr1);
    MB_ROW_DEC *mbrd = (MB_ROW_DEC *)(((DECODETHREAD_DATA *)p_data)->ptr2);
    ENTROPY_CONTEXT_PLANES mb_row_left_context;

 while (1)
 {
 if (pbi->b_multithreaded_rd == 0)
 break;

 if (sem_wait(&pbi->h_event_start_decoding[ithread]) == 0)
 {
 if (pbi->b_multithreaded_rd == 0)
 break;
 else
 {
                MACROBLOCKD *xd = &mbrd->mbd;
                xd->left_context = &mb_row_left_context;

                mt_decode_mb_rows(pbi, xd, ithread+1);
 }
 }
 }

 return 0 ;
}
