Luv24toLuv48(LogLuvState* sp, uint8* op, tmsize_t n)
{
	uint32* luv = (uint32*) sp->tbuf;  
	int16* luv3 = (int16*) op;

	while (n-- > 0) {
		double u, v;

		*luv3++ = (int16)((*luv >> 12 & 0xffd) + 13314);
		if (uv_decode(&u, &v, *luv&0x3fff) < 0) {
			u = U_NEU;
			v = V_NEU;
		}
		*luv3++ = (int16)(u * (1L<<15));
		*luv3++ = (int16)(v * (1L<<15));
		luv++;
	}
}
