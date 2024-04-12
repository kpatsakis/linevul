OJPEGReadWord(OJPEGState* sp, uint16* word)
{
	uint8 m;
	if (OJPEGReadByte(sp,&m)==0)
		return(0);
	*word=(m<<8);
	if (OJPEGReadByte(sp,&m)==0)
		return(0);
	*word|=m;
	return(1);
}
