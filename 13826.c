void h264bsdInitRefPicList(dpbStorage_t *dpb)
{

/* Variables */

    u32 i;

/* Code */

 for (i = 0; i < dpb->numRefFrames; i++)
        dpb->list[i] = &dpb->buffer[i];

}
