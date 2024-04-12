bool omx_venc::dev_set_buf_req(OMX_U32 *min_buff_count,
        OMX_U32 *actual_buff_count,
        OMX_U32 *buff_size,
        OMX_U32 port)
{
 return handle->venc_set_buf_req(min_buff_count,
            actual_buff_count,
            buff_size,
            port);

}
