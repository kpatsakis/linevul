static inline void set_poll(poll_slot_t* ps, int fd, int type, int flags, uint32_t user_id)
{
    ps->pfd.fd = fd;
    ps->user_id = user_id;
 if(ps->type != 0 && ps->type != type)
        APPL_TRACE_ERROR("poll socket type should not changed! type was:%d, type now:%d", ps->type, type);
    ps->type = type;
    ps->flags = flags;
    ps->pfd.events = flags2pevents(flags);
    ps->pfd.revents = 0;
}
