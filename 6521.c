static ieee754sp fpemu_sp_rsqrt(ieee754sp s)
{
	return ieee754sp_div(ieee754sp_one(0), ieee754sp_sqrt(s));
}
