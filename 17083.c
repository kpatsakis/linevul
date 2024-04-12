uriCommonTest(const char *filename,
             const char *result,
             const char *err,
             const char *base) {
    char *temp;
    FILE *o, *f;
    char str[1024];
    int res = 0, i, ret;

    temp = resultFilename(filename, "", ".res");
    if (temp == NULL) {
        fprintf(stderr, "Out of memory\n");
        fatalError();
    }
    o = fopen(temp, "wb");
    if (o == NULL) {
	fprintf(stderr, "failed to open output file %s\n", temp);
        free(temp);
	return(-1);
    }
    f = fopen(filename, "rb");
    if (f == NULL) {
	fprintf(stderr, "failed to open input file %s\n", filename);
	fclose(o);
        if (temp != NULL) {
            unlink(temp);
            free(temp);
        }
	return(-1);
    }

    while (1) {
	/*
	 * read one line in string buffer.
	 */
	if (fgets (&str[0], sizeof (str) - 1, f) == NULL)
	   break;

	/*
	 * remove the ending spaces
	 */
	i = strlen(str);
	while ((i > 0) &&
	       ((str[i - 1] == '\n') || (str[i - 1] == '\r') ||
		(str[i - 1] == ' ') || (str[i - 1] == '\t'))) {
	    i--;
	    str[i] = 0;
	}
	nb_tests++;
	handleURI(str, base, o);
    }

    fclose(f);
    fclose(o);

    if (result != NULL) {
	ret = compareFiles(temp, result);
	if (ret) {
	    fprintf(stderr, "Result for %s failed in %s\n", filename, result);
	    res = 1;
	}
    }
    if (err != NULL) {
	ret = compareFileMem(err, testErrors, testErrorsSize);
	if (ret != 0) {
	    fprintf(stderr, "Error for %s failed\n", filename);
	    res = 1;
	}
    }

    if (temp != NULL) {
        unlink(temp);
        free(temp);
    }
    return(res);
}
