static int bmpr_has_transparency(struct iw_image *img)
{
	int i,j;

	if(img->imgtype!=IW_IMGTYPE_RGBA) return 0;

	for(j=0;j<img->height;j++) {
		for(i=0;i<img->width;i++) {
			if(img->pixels[j*img->bpr + i*4 + 3] != 255)
				return 1;
		}
	}
	return 0;
}
