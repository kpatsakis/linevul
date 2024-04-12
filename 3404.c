OMX_ERRORTYPE omx_vdec::allocate_color_convert_buf::free_output_buffer(
        OMX_BUFFERHEADERTYPE *bufhdr)
{
 unsigned int index = 0;

 if (!enabled)
 return omx->free_output_buffer(bufhdr);
 if (enabled && omx->is_component_secure())
 return OMX_ErrorNone;
 if (!allocated_count || !bufhdr) {
        DEBUG_PRINT_ERROR("Color convert no buffer to be freed %p",bufhdr);
 return OMX_ErrorBadParameter;
 }
    index = bufhdr - m_out_mem_ptr_client;
 if (index >= omx->drv_ctx.op_buf.actualcount) {
        DEBUG_PRINT_ERROR("Incorrect index color convert free_output_buffer");
 return OMX_ErrorBadParameter;
 }
 if (pmem_fd[index] > 0) {
        munmap(pmem_baseaddress[index], buffer_size_req);
        close(pmem_fd[index]);
 }
    pmem_fd[index] = -1;
#ifdef USE_ION
    omx->free_ion_memory(&op_buf_ion_info[index]);
#endif
    m_heap_ptr[index].video_heap_ptr = NULL;
 if (allocated_count > 0)
        allocated_count--;
 else
        allocated_count = 0;
 if (!allocated_count) {
        pthread_mutex_lock(&omx->c_lock);
        c2d.close();
        init_members();
        pthread_mutex_unlock(&omx->c_lock);
 }
 return omx->free_output_buffer(&omx->m_out_mem_ptr[index]);
}
