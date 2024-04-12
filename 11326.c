static void readTiff8bit (const unsigned char *src,
                          gdImagePtr im,
                          uint16       photometric,
                          int          startx,
                          int          starty,
                          int          width,
                          int          height,
                          char         has_alpha,
                          int          extra,
                          int          align)
{
	int    red, green, blue, alpha;
	int    x, y;

	(void)extra;
	(void)align;

	switch (photometric) {
	case PHOTOMETRIC_PALETTE:
		/* Palette has no alpha (see TIFF specs for more details */
		for (y = starty; y < starty + height; y++) {
			for (x = startx; x < startx + width; x++) {
				gdImageSetPixel(im, x, y,*(src++));
			}
		}
		break;

	case PHOTOMETRIC_RGB:
		if (has_alpha) {
			gdImageAlphaBlending(im, 0);
			gdImageSaveAlpha(im, 1);

			for (y = starty; y < starty + height; y++) {
				for (x = startx; x < startx + width; x++) {
					red   = *src++;
					green = *src++;
					blue  = *src++;
					alpha = *src++;
					red   = MIN (red, alpha);
					blue  = MIN (blue, alpha);
					green = MIN (green, alpha);

					if (alpha) {
						gdImageSetPixel(im, x, y, gdTrueColorAlpha(red * 255 / alpha, green * 255 / alpha, blue * 255 /alpha, gdAlphaMax - (alpha >> 1)));
					} else {
						gdImageSetPixel(im, x, y, gdTrueColorAlpha(red, green, blue, gdAlphaMax - (alpha >> 1)));
					}
				}
			}

		} else {
			for (y = 0; y < height; y++) {
				for (x = 0; x < width; x++) {
					register unsigned char r = *src++;
					register unsigned char g = *src++;
					register unsigned char b = *src++;

					gdImageSetPixel(im, x, y, gdTrueColor(r, g, b));
				}
			}
		}
		break;

	case PHOTOMETRIC_MINISWHITE:
		if (has_alpha) {
			/* We don't process the extra yet */
		} else {
			for (y = starty; y < starty + height; y++) {
				for (x = startx; x < startx + width; x++) {
					gdImageSetPixel(im, x, y, ~(*src++));
				}
			}
		}
		break;

	case PHOTOMETRIC_MINISBLACK:
		if (has_alpha) {
			/* We don't process the extra yet */
		} else {
			for (y = starty; y < height; y++) {
				for (x = 0; x < width; x++) {
					gdImageSetPixel(im, x, y, *src++);
				}
			}
		}
		break;
	}
}
