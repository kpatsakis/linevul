OMX_ERRORTYPE  omx_vdec::allocate_input_buffer(
        OMX_IN OMX_HANDLETYPE            hComp,
        OMX_INOUT OMX_BUFFERHEADERTYPE** bufferHdr,
        OMX_IN OMX_U32                   port,
        OMX_IN OMX_PTR                   appData,
        OMX_IN OMX_U32                   bytes)
{
    OMX_ERRORTYPE eRet = OMX_ErrorNone;
 struct vdec_setbuffer_cmd setbuffers;
    OMX_BUFFERHEADERTYPE *input = NULL;
 unsigned   i = 0;
 unsigned char *buf_addr = NULL;
 int pmem_fd = -1;

 (void) hComp;
 (void) port;


 if (bytes != drv_ctx.ip_buf.buffer_size) {
        DEBUG_PRINT_LOW("Requested Size is wrong %u epected is %u",
 (unsigned int)bytes, (unsigned int)drv_ctx.ip_buf.buffer_size);
 return OMX_ErrorBadParameter;
 }

 if (!m_inp_mem_ptr) {
        DEBUG_PRINT_HIGH("Allocate i/p buffer Header: Cnt(%d) Sz(%u)",
                drv_ctx.ip_buf.actualcount,
 (unsigned int)drv_ctx.ip_buf.buffer_size);

        m_inp_mem_ptr = (OMX_BUFFERHEADERTYPE*) \
                calloc( (sizeof(OMX_BUFFERHEADERTYPE)), drv_ctx.ip_buf.actualcount);

 if (m_inp_mem_ptr == NULL) {
 return OMX_ErrorInsufficientResources;
 }

        drv_ctx.ptr_inputbuffer = (struct vdec_bufferpayload *) \
                      calloc ((sizeof (struct vdec_bufferpayload)),drv_ctx.ip_buf.actualcount);

 if (drv_ctx.ptr_inputbuffer == NULL) {
 return OMX_ErrorInsufficientResources;
 }
#ifdef USE_ION
        drv_ctx.ip_buf_ion_info = (struct vdec_ion *) \
                      calloc ((sizeof (struct vdec_ion)),drv_ctx.ip_buf.actualcount);

 if (drv_ctx.ip_buf_ion_info == NULL) {
 return OMX_ErrorInsufficientResources;
 }
#endif

 for (i=0; i < drv_ctx.ip_buf.actualcount; i++) {
            drv_ctx.ptr_inputbuffer [i].pmem_fd = -1;
#ifdef USE_ION
            drv_ctx.ip_buf_ion_info[i].ion_device_fd = -1;
#endif
 }
 }

 for (i=0; i< drv_ctx.ip_buf.actualcount; i++) {
 if (BITMASK_ABSENT(&m_inp_bm_count,i)) {
            DEBUG_PRINT_LOW("Free Input Buffer Index %d",i);
 break;
 }
 }

 if (i < drv_ctx.ip_buf.actualcount) {
 struct v4l2_buffer buf;
 struct v4l2_plane plane;
 int rc;
        DEBUG_PRINT_LOW("Allocate input Buffer");
#ifdef USE_ION
        drv_ctx.ip_buf_ion_info[i].ion_device_fd = alloc_map_ion_memory(
                drv_ctx.ip_buf.buffer_size,drv_ctx.op_buf.alignment,
 &drv_ctx.ip_buf_ion_info[i].ion_alloc_data,
 &drv_ctx.ip_buf_ion_info[i].fd_ion_data, secure_mode ? ION_SECURE
#ifndef DISABLE_INPUT_BUFFER_CACHE
 : ION_FLAG_CACHED
#else
 : 0
#endif
 );
 if (drv_ctx.ip_buf_ion_info[i].ion_device_fd < 0) {
 return OMX_ErrorInsufficientResources;
 }
        pmem_fd = drv_ctx.ip_buf_ion_info[i].fd_ion_data.fd;
#else
        pmem_fd = open (MEM_DEVICE,O_RDWR);

 if (pmem_fd < 0) {
            DEBUG_PRINT_ERROR("open failed for pmem/adsp for input buffer");
 return OMX_ErrorInsufficientResources;
 }

 if (pmem_fd == 0) {
            pmem_fd = open (MEM_DEVICE,O_RDWR);

 if (pmem_fd < 0) {
                DEBUG_PRINT_ERROR("open failed for pmem/adsp for input buffer");
 return OMX_ErrorInsufficientResources;
 }
 }

 if (!align_pmem_buffers(pmem_fd, drv_ctx.ip_buf.buffer_size,
                    drv_ctx.ip_buf.alignment)) {
            DEBUG_PRINT_ERROR("align_pmem_buffers() failed");
            close(pmem_fd);
 return OMX_ErrorInsufficientResources;
 }
#endif
 if (!secure_mode) {
            buf_addr = (unsigned char *)mmap(NULL,
                    drv_ctx.ip_buf.buffer_size,
                    PROT_READ|PROT_WRITE, MAP_SHARED, pmem_fd, 0);

 if (buf_addr == MAP_FAILED) {
                close(pmem_fd);
#ifdef USE_ION
                free_ion_memory(&drv_ctx.ip_buf_ion_info[i]);
#endif
                DEBUG_PRINT_ERROR("Map Failed to allocate input buffer");
 return OMX_ErrorInsufficientResources;
 }
 }
 *bufferHdr = (m_inp_mem_ptr + i);
 if (secure_mode)
            drv_ctx.ptr_inputbuffer [i].bufferaddr = *bufferHdr;
 else
            drv_ctx.ptr_inputbuffer [i].bufferaddr = buf_addr;
        drv_ctx.ptr_inputbuffer [i].pmem_fd = pmem_fd;
        drv_ctx.ptr_inputbuffer [i].buffer_len = drv_ctx.ip_buf.buffer_size;
        drv_ctx.ptr_inputbuffer [i].mmaped_size = drv_ctx.ip_buf.buffer_size;
        drv_ctx.ptr_inputbuffer [i].offset = 0;


        buf.index = i;
        buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
        buf.memory = V4L2_MEMORY_USERPTR;
        plane.bytesused = 0;
        plane.length = drv_ctx.ptr_inputbuffer [i].mmaped_size;
        plane.m.userptr = (unsigned long)drv_ctx.ptr_inputbuffer[i].bufferaddr;
        plane.reserved[0] =drv_ctx.ptr_inputbuffer [i].pmem_fd;
        plane.reserved[1] = 0;
        plane.data_offset = drv_ctx.ptr_inputbuffer[i].offset;
        buf.m.planes = &plane;
        buf.length = 1;

        DEBUG_PRINT_LOW("Set the input Buffer Idx: %d Addr: %p", i,
                drv_ctx.ptr_inputbuffer[i].bufferaddr);

        rc = ioctl(drv_ctx.video_driver_fd, VIDIOC_PREPARE_BUF, &buf);

 if (rc) {
            DEBUG_PRINT_ERROR("Failed to prepare bufs");
 /*TODO: How to handle this case */
 return OMX_ErrorInsufficientResources;
 }

        input = *bufferHdr;
        BITMASK_SET(&m_inp_bm_count,i);
        DEBUG_PRINT_LOW("Buffer address %p of pmem",*bufferHdr);
 if (secure_mode)
            input->pBuffer = (OMX_U8 *)(intptr_t)drv_ctx.ptr_inputbuffer [i].pmem_fd;
 else
            input->pBuffer           = (OMX_U8 *)buf_addr;
        input->nSize             = sizeof(OMX_BUFFERHEADERTYPE);
        input->nVersion.nVersion = OMX_SPEC_VERSION;
        input->nAllocLen         = drv_ctx.ip_buf.buffer_size;
        input->pAppPrivate       = appData;
        input->nInputPortIndex   = OMX_CORE_INPUT_PORT_INDEX;
        input->pInputPortPrivate = (void *)&drv_ctx.ptr_inputbuffer [i];

 if (drv_ctx.disable_dmx) {
            eRet = allocate_desc_buffer(i);
 }
 } else {
        DEBUG_PRINT_ERROR("ERROR:Input Buffer Index not found");
        eRet = OMX_ErrorInsufficientResources;
 }
 return eRet;
}
