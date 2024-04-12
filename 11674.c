bool omx_vdec::omx_cmd_queue::insert_entry(unsigned long p1, unsigned long p2, unsigned long id)
{
 bool ret = true;
 if (m_size < OMX_CORE_CONTROL_CMDQ_SIZE) {
        m_q[m_write].id       = id;
        m_q[m_write].param1   = p1;
        m_q[m_write].param2   = p2;
        m_write++;
        m_size ++;
 if (m_write >= OMX_CORE_CONTROL_CMDQ_SIZE) {
            m_write = 0;
 }
 } else {
        ret = false;
        DEBUG_PRINT_ERROR("ERROR: %s()::Command Queue Full", __func__);
 }
 return ret;
}
