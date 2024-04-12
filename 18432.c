OMX_BUFFERHEADERTYPE* omx_vdec::allocate_color_convert_buf::get_il_buf_hdr()
{
 if (!omx) {
        DEBUG_PRINT_ERROR("Invalid param get_buf_hdr");
 return NULL;
 }
 if (!enabled)
 return omx->m_out_mem_ptr;
 return m_out_mem_ptr_client;
}
