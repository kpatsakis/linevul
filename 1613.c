convert_size3(clen_t size)
{
    Str tmp = Strnew();
    int n;

    do {
	n = size % 1000;
	size /= 1000;
	tmp = Sprintf(size ? ",%.3d%s" : "%d%s", n, tmp->ptr);
    } while (size);
    return tmp->ptr;
}
