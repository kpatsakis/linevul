void CL_DemoFilename( int number, char *fileName, int fileNameSize ) {
	int a,b,c,d;

	if(number < 0 || number > 9999)
		number = 9999;

	a = number / 1000;
	number -= a * 1000;
	b = number / 100;
	number -= b * 100;
	c = number / 10;
	number -= c * 10;
	d = number;

	Com_sprintf( fileName, fileNameSize, "demo%i%i%i%i"
				 , a, b, c, d );
}
