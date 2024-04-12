void vp8_decoder_create_threads(VP8D_COMP *pbi)
{
 int core_count = 0;
 unsigned int ithread;

    pbi->b_multithreaded_rd = 0;
    pbi->allocated_decoding_thread_count = 0;

 /* limit decoding threads to the max number of token partitions */
    core_count = (pbi->max_threads > 8) ? 8 : pbi->max_threads;

 /* limit decoding threads to the available cores */
 if (core_count > pbi->common.processor_core_count)
        core_count = pbi->common.processor_core_count;

 if (core_count > 1)
 {
        pbi->b_multithreaded_rd = 1;
        pbi->decoding_thread_count = core_count - 1;

        CALLOC_ARRAY(pbi->h_decoding_thread, pbi->decoding_thread_count);
        CALLOC_ARRAY(pbi->h_event_start_decoding, pbi->decoding_thread_count);
        CALLOC_ARRAY_ALIGNED(pbi->mb_row_di, pbi->decoding_thread_count, 32);
        CALLOC_ARRAY(pbi->de_thread_data, pbi->decoding_thread_count);

 for (ithread = 0; ithread < pbi->decoding_thread_count; ithread++)
 {
            sem_init(&pbi->h_event_start_decoding[ithread], 0, 0);

            vp8_setup_block_dptrs(&pbi->mb_row_di[ithread].mbd);

            pbi->de_thread_data[ithread].ithread  = ithread;
            pbi->de_thread_data[ithread].ptr1     = (void *)pbi;
            pbi->de_thread_data[ithread].ptr2     = (void *) &pbi->mb_row_di[ithread];

            pthread_create(&pbi->h_decoding_thread[ithread], 0, thread_decoding_proc, (&pbi->de_thread_data[ithread]));
 }

        sem_init(&pbi->h_event_end_decoding, 0, 0);

        pbi->allocated_decoding_thread_count = pbi->decoding_thread_count;
 }

 }
