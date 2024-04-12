ProcShmAttach(ClientPtr client)
{
    SHMSTAT_TYPE buf;
    ShmDescPtr shmdesc;

    REQUEST(xShmAttachReq);

    REQUEST_SIZE_MATCH(xShmAttachReq);
    LEGAL_NEW_RESOURCE(stuff->shmseg, client);
    if ((stuff->readOnly != xTrue) && (stuff->readOnly != xFalse)) {
        client->errorValue = stuff->readOnly;
        return BadValue;
    }
    for (shmdesc = Shmsegs; shmdesc; shmdesc = shmdesc->next) {
        if (!SHMDESC_IS_FD(shmdesc) && shmdesc->shmid == stuff->shmid)
            break;
    }
    if (shmdesc) {
        if (!stuff->readOnly && !shmdesc->writable)
            return BadAccess;
        shmdesc->refcnt++;
    }
    else {
        shmdesc = malloc(sizeof(ShmDescRec));
        if (!shmdesc)
            return BadAlloc;
#ifdef SHM_FD_PASSING
        shmdesc->is_fd = FALSE;
#endif
        shmdesc->addr = shmat(stuff->shmid, 0,
                              stuff->readOnly ? SHM_RDONLY : 0);
        if ((shmdesc->addr == ((char *) -1)) || SHMSTAT(stuff->shmid, &buf)) {
            free(shmdesc);
            return BadAccess;
        }

        /* The attach was performed with root privs. We must
         * do manual checking of access rights for the credentials
         * of the client */

        if (shm_access(client, &(SHM_PERM(buf)), stuff->readOnly) == -1) {
            shmdt(shmdesc->addr);
            free(shmdesc);
            return BadAccess;
        }

        shmdesc->shmid = stuff->shmid;
        shmdesc->refcnt = 1;
        shmdesc->writable = !stuff->readOnly;
        shmdesc->size = SHM_SEGSZ(buf);
        shmdesc->next = Shmsegs;
        Shmsegs = shmdesc;
    }
    if (!AddResource(stuff->shmseg, ShmSegType, (void *) shmdesc))
        return BadAlloc;
    return Success;
}
