static TEMPO ConvertTempo(uint16 ciaSpeed)
{
	return TEMPO((125.0 * 3546.0) / ciaSpeed);
}
