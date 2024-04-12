dpbPicture_t* FindSmallestPicOrderCnt(dpbStorage_t *dpb)
{

/* Variables */

    u32 i;
    i32 picOrderCnt;
 dpbPicture_t *tmp;

/* Code */

    ASSERT(dpb);

    picOrderCnt = 0x7FFFFFFF;
    tmp = NULL;

 for (i = 0; i <= dpb->dpbSize; i++)
 {
 if (dpb->buffer[i].toBeDisplayed &&
 (dpb->buffer[i].picOrderCnt < picOrderCnt))
 {
            tmp = dpb->buffer + i;
            picOrderCnt = dpb->buffer[i].picOrderCnt;
 }
 }

 return(tmp);

}
