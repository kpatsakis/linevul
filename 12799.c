qboolean CL_CheckPaused(void)
{
	if(cl_paused->integer || cl_paused->modified)
		return qtrue;
	
	return qfalse;
}
