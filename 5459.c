static u32 Mmcop2(dpbStorage_t *dpb, u32 longTermPicNum)
{

/* Variables */

    i32 index;

/* Code */

    index = FindDpbPic(dpb, (i32)longTermPicNum, HANTRO_FALSE);
 if (index < 0)
 return(HANTRO_NOK);

    SET_UNUSED(dpb->buffer[index]);
    dpb->numRefFrames--;
 if (!dpb->buffer[index].toBeDisplayed)
        dpb->fullness--;

 return(HANTRO_OK);

}
