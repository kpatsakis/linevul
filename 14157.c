u32 _ilog_(u32 v)
{
	u32 ret=0;
	while(v) {
		ret++;
		v>>=1;
	}
	return(ret);
}
