Luv24toRGB(LogLuvState* sp, uint8* op, tmsize_t n)
{
	uint32* luv = (uint32*) sp->tbuf;  
	uint8* rgb = (uint8*) op;

	while (n-- > 0) {
		float xyz[3];

		LogLuv24toXYZ(*luv++, xyz);
		XYZtoRGB24(xyz, rgb);
		rgb += 3;
	}
}
