OMX_ERRORTYPE omx_vdec::push_input_h264 (OMX_HANDLETYPE hComp)
{
    OMX_U32 partial_frame = 1;
 unsigned long address = 0, p2 = 0, id = 0;
    OMX_BOOL isNewFrame = OMX_FALSE;
    OMX_BOOL generate_ebd = OMX_TRUE;

 if (h264_scratch.pBuffer == NULL) {
        DEBUG_PRINT_ERROR("ERROR:H.264 Scratch Buffer not allocated");
 return OMX_ErrorBadParameter;
 }
    DEBUG_PRINT_LOW("Pending h264_scratch.nFilledLen %u "
 "look_ahead_nal %d", (unsigned int)h264_scratch.nFilledLen, look_ahead_nal);
    DEBUG_PRINT_LOW("Pending pdest_frame->nFilledLen %u",(unsigned int)pdest_frame->nFilledLen);
 if (h264_scratch.nFilledLen && look_ahead_nal) {
        look_ahead_nal = false;
 if ((pdest_frame->nAllocLen - pdest_frame->nFilledLen) >=
                h264_scratch.nFilledLen) {
            memcpy ((pdest_frame->pBuffer + pdest_frame->nFilledLen),
                    h264_scratch.pBuffer,h264_scratch.nFilledLen);
            pdest_frame->nFilledLen += h264_scratch.nFilledLen;
            DEBUG_PRINT_LOW("Copy the previous NAL (h264 scratch) into Dest frame");
            h264_scratch.nFilledLen = 0;
 } else {
            DEBUG_PRINT_ERROR("Error:1: Destination buffer overflow for H264");
 return OMX_ErrorBadParameter;
 }
 }

 /* If an empty input is queued with EOS, do not coalesce with the destination-frame yet, as this may result
       in EOS flag getting associated with the destination
    */
 if (!psource_frame->nFilledLen && (psource_frame->nFlags & OMX_BUFFERFLAG_EOS) &&
            pdest_frame->nFilledLen) {
        DEBUG_PRINT_HIGH("delay ETB for 'empty buffer with EOS'");
        generate_ebd = OMX_FALSE;
 }

 if (nal_length == 0) {
        DEBUG_PRINT_LOW("Zero NAL, hence parse using start code");
 if (m_frame_parser.parse_sc_frame(psource_frame,
 &h264_scratch,&partial_frame) == -1) {
            DEBUG_PRINT_ERROR("Error In Parsing Return Error");
 return OMX_ErrorBadParameter;
 }
 } else {
        DEBUG_PRINT_LOW("Non-zero NAL length clip, hence parse with NAL size %d ",nal_length);
 if (m_frame_parser.parse_h264_nallength(psource_frame,
 &h264_scratch,&partial_frame) == -1) {
            DEBUG_PRINT_ERROR("Error In Parsing NAL size, Return Error");
 return OMX_ErrorBadParameter;
 }
 }

 if (partial_frame == 0) {
 if (nal_count == 0 && h264_scratch.nFilledLen == 0) {
            DEBUG_PRINT_LOW("First NAL with Zero Length, hence Skip");
            nal_count++;
            h264_scratch.nTimeStamp = psource_frame->nTimeStamp;
            h264_scratch.nFlags = psource_frame->nFlags;
 } else {
            DEBUG_PRINT_LOW("Parsed New NAL Length = %u",(unsigned int)h264_scratch.nFilledLen);
 if (h264_scratch.nFilledLen) {
                h264_parser->parse_nal((OMX_U8*)h264_scratch.pBuffer, h264_scratch.nFilledLen,
                        NALU_TYPE_SPS);
#ifndef PROCESS_EXTRADATA_IN_OUTPUT_PORT
 if (client_extradata & OMX_TIMEINFO_EXTRADATA)
                    h264_parser->parse_nal((OMX_U8*)h264_scratch.pBuffer,
                            h264_scratch.nFilledLen, NALU_TYPE_SEI);
 else if (client_extradata & OMX_FRAMEINFO_EXTRADATA)
                    h264_parser->parse_nal((OMX_U8*)h264_scratch.pBuffer,
                            h264_scratch.nFilledLen, NALU_TYPE_SEI);
#endif
                m_frame_parser.mutils->isNewFrame(&h264_scratch, 0, isNewFrame);
                nal_count++;
 if (VALID_TS(h264_last_au_ts) && !VALID_TS(pdest_frame->nTimeStamp)) {
                    pdest_frame->nTimeStamp = h264_last_au_ts;
                    pdest_frame->nFlags = h264_last_au_flags;
#ifdef PANSCAN_HDLR
 if (client_extradata & OMX_FRAMEINFO_EXTRADATA)
                        h264_parser->update_panscan_data(h264_last_au_ts);
#endif
 }
 if (m_frame_parser.mutils->nalu_type == NALU_TYPE_NON_IDR ||
                        m_frame_parser.mutils->nalu_type == NALU_TYPE_IDR) {
                    h264_last_au_ts = h264_scratch.nTimeStamp;
                    h264_last_au_flags = h264_scratch.nFlags;
#ifndef PROCESS_EXTRADATA_IN_OUTPUT_PORT
 if (client_extradata & OMX_TIMEINFO_EXTRADATA) {
                        OMX_S64 ts_in_sei = h264_parser->process_ts_with_sei_vui(h264_last_au_ts);
 if (!VALID_TS(h264_last_au_ts))
                            h264_last_au_ts = ts_in_sei;
 }
#endif
 } else
                    h264_last_au_ts = LLONG_MAX;
 }

 if (!isNewFrame) {
 if ( (pdest_frame->nAllocLen - pdest_frame->nFilledLen) >=
                        h264_scratch.nFilledLen) {
                    DEBUG_PRINT_LOW("Not a NewFrame Copy into Dest len %u",
 (unsigned int)h264_scratch.nFilledLen);
                    memcpy ((pdest_frame->pBuffer + pdest_frame->nFilledLen),
                            h264_scratch.pBuffer,h264_scratch.nFilledLen);
                    pdest_frame->nFilledLen += h264_scratch.nFilledLen;
 if (m_frame_parser.mutils->nalu_type == NALU_TYPE_EOSEQ)
                        pdest_frame->nFlags |= QOMX_VIDEO_BUFFERFLAG_EOSEQ;
                    h264_scratch.nFilledLen = 0;
 } else {
                    DEBUG_PRINT_LOW("Error:2: Destination buffer overflow for H264");
 return OMX_ErrorBadParameter;
 }
 } else if(h264_scratch.nFilledLen) {
                look_ahead_nal = true;
                DEBUG_PRINT_LOW("Frame Found start Decoding Size =%u TimeStamp = %llu",
 (unsigned int)pdest_frame->nFilledLen,pdest_frame->nTimeStamp);
                DEBUG_PRINT_LOW("Found a frame size = %u number = %d",
 (unsigned int)pdest_frame->nFilledLen,frame_count++);

 if (pdest_frame->nFilledLen == 0) {
                    DEBUG_PRINT_LOW("Copy the Current Frame since and push it");
                    look_ahead_nal = false;
 if ( (pdest_frame->nAllocLen - pdest_frame->nFilledLen) >=
                            h264_scratch.nFilledLen) {
                        memcpy ((pdest_frame->pBuffer + pdest_frame->nFilledLen),
                                h264_scratch.pBuffer,h264_scratch.nFilledLen);
                        pdest_frame->nFilledLen += h264_scratch.nFilledLen;
                        h264_scratch.nFilledLen = 0;
 } else {
                        DEBUG_PRINT_ERROR("Error:3: Destination buffer overflow for H264");
 return OMX_ErrorBadParameter;
 }
 } else {
 if (psource_frame->nFilledLen || h264_scratch.nFilledLen) {
                        DEBUG_PRINT_LOW("Reset the EOS Flag");
                        pdest_frame->nFlags &= ~OMX_BUFFERFLAG_EOS;
 }
 /*Push the frame to the Decoder*/
 if (empty_this_buffer_proxy(hComp,pdest_frame) != OMX_ErrorNone) {
 return OMX_ErrorBadParameter;
 }
                    pdest_frame = NULL;
 if (m_input_free_q.m_size) {
                        m_input_free_q.pop_entry(&address,&p2,&id);
                        pdest_frame = (OMX_BUFFERHEADERTYPE *) address;
                        DEBUG_PRINT_LOW("Pop the next pdest_buffer %p",pdest_frame);
                        pdest_frame->nFilledLen = 0;
                        pdest_frame->nFlags = 0;
                        pdest_frame->nTimeStamp = LLONG_MAX;
 }
 }
 }
 }
 } else {
        DEBUG_PRINT_LOW("Not a Complete Frame, pdest_frame->nFilledLen %u", (unsigned int)pdest_frame->nFilledLen);
 /*Check if Destination Buffer is full*/
 if (h264_scratch.nAllocLen ==
                h264_scratch.nFilledLen + h264_scratch.nOffset) {
            DEBUG_PRINT_ERROR("ERROR: Frame Not found though Destination Filled");
 return OMX_ErrorStreamCorrupt;
 }
 }

 if (!psource_frame->nFilledLen) {
        DEBUG_PRINT_LOW("Buffer Consumed return source %p back to client",psource_frame);

 if (psource_frame->nFlags & OMX_BUFFERFLAG_EOS) {
 if (pdest_frame) {
                DEBUG_PRINT_LOW("EOS Reached Pass Last Buffer");
 if ( (pdest_frame->nAllocLen - pdest_frame->nFilledLen) >=
                        h264_scratch.nFilledLen) {
 if(pdest_frame->nFilledLen == 0) {
 /* No residual frame from before, send whatever
                         * we have left */
                        memcpy((pdest_frame->pBuffer + pdest_frame->nFilledLen),
                                h264_scratch.pBuffer, h264_scratch.nFilledLen);
                        pdest_frame->nFilledLen += h264_scratch.nFilledLen;
                        h264_scratch.nFilledLen = 0;
                        pdest_frame->nTimeStamp = h264_scratch.nTimeStamp;
 } else {
                        m_frame_parser.mutils->isNewFrame(&h264_scratch, 0, isNewFrame);
 if(!isNewFrame) {
 /* Have a residual frame, but we know that the
                             * AU in this frame is belonging to whatever
                             * frame we had left over.  So append it */
                             memcpy ((pdest_frame->pBuffer + pdest_frame->nFilledLen),
                                     h264_scratch.pBuffer,h264_scratch.nFilledLen);
                             pdest_frame->nFilledLen += h264_scratch.nFilledLen;
                             h264_scratch.nFilledLen = 0;
 if (h264_last_au_ts != LLONG_MAX)
                             pdest_frame->nTimeStamp = h264_last_au_ts;
 } else {
 /* Completely new frame, let's just push what
                             * we have now.  The resulting EBD would trigger
                             * another push */
                            generate_ebd = OMX_FALSE;
                            pdest_frame->nTimeStamp = h264_last_au_ts;
                            h264_last_au_ts = h264_scratch.nTimeStamp;
 }
 }
 } else {
                    DEBUG_PRINT_ERROR("ERROR:4: Destination buffer overflow for H264");
 return OMX_ErrorBadParameter;
 }

 /* Iff we coalesced two buffers, inherit the flags of both bufs */
 if(generate_ebd == OMX_TRUE) {
                     pdest_frame->nFlags = h264_scratch.nFlags | psource_frame->nFlags;
 }

                DEBUG_PRINT_LOW("pdest_frame->nFilledLen =%u TimeStamp = %llu",
 (unsigned int)pdest_frame->nFilledLen,pdest_frame->nTimeStamp);
                DEBUG_PRINT_LOW("Push AU frame number %d to driver", frame_count++);
#ifndef PROCESS_EXTRADATA_IN_OUTPUT_PORT
 if (client_extradata & OMX_TIMEINFO_EXTRADATA) {
                    OMX_S64 ts_in_sei = h264_parser->process_ts_with_sei_vui(pdest_frame->nTimeStamp);
 if (!VALID_TS(pdest_frame->nTimeStamp))
                        pdest_frame->nTimeStamp = ts_in_sei;
 }
#endif
 /*Push the frame to the Decoder*/
 if (empty_this_buffer_proxy(hComp,pdest_frame) != OMX_ErrorNone) {
 return OMX_ErrorBadParameter;
 }
                frame_count++;
                pdest_frame = NULL;
 } else {
                DEBUG_PRINT_LOW("Last frame in else dest addr %p size %u",
                        pdest_frame, (unsigned int)h264_scratch.nFilledLen);
                generate_ebd = OMX_FALSE;
 }
 }
 }
 if (generate_ebd && !psource_frame->nFilledLen) {
        m_cb.EmptyBufferDone (hComp,m_app_data,psource_frame);
        psource_frame = NULL;
 if (m_input_pending_q.m_size) {
            DEBUG_PRINT_LOW("Pull Next source Buffer %p",psource_frame);
            m_input_pending_q.pop_entry(&address,&p2,&id);
            psource_frame = (OMX_BUFFERHEADERTYPE *) address;
            DEBUG_PRINT_LOW("Next source Buffer flag %u src length %u",
 (unsigned int)psource_frame->nFlags, (unsigned int)psource_frame->nFilledLen);
 }
 }
 return OMX_ErrorNone;
}
