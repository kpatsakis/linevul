launchTests(testDescPtr tst) {
    int res = 0, err = 0;
    size_t i;
    char *result;
    char *error;
    int mem;

    if (tst == NULL) return(-1);
    if (tst->in != NULL) {
	glob_t globbuf;

	globbuf.gl_offs = 0;
	glob(tst->in, GLOB_DOOFFS, NULL, &globbuf);
	for (i = 0;i < globbuf.gl_pathc;i++) {
	    if (!checkTestFile(globbuf.gl_pathv[i]))
	        continue;
	    if (tst->suffix != NULL) {
		result = resultFilename(globbuf.gl_pathv[i], tst->out,
					tst->suffix);
		if (result == NULL) {
		    fprintf(stderr, "Out of memory !\n");
		    fatalError();
		}
	    } else {
	        result = NULL;
	    }
	    if (tst->err != NULL) {
		error = resultFilename(globbuf.gl_pathv[i], tst->out,
		                        tst->err);
		if (error == NULL) {
		    fprintf(stderr, "Out of memory !\n");
		    fatalError();
		}
	    } else {
	        error = NULL;
	    }
	    if ((result) &&(!checkTestFile(result)) && !update_results) {
	        fprintf(stderr, "Missing result file %s\n", result);
	    } else if ((error) &&(!checkTestFile(error)) && !update_results) {
	        fprintf(stderr, "Missing error file %s\n", error);
	    } else {
		mem = xmlMemUsed();
		extraMemoryFromResolver = 0;
		testErrorsSize = 0;
		testErrors[0] = 0;
		res = tst->func(globbuf.gl_pathv[i], result, error,
		                tst->options | XML_PARSE_COMPACT);
		xmlResetLastError();
		if (res != 0) {
		    fprintf(stderr, "File %s generated an error\n",
		            globbuf.gl_pathv[i]);
		    nb_errors++;
		    err++;
		}
		else if (xmlMemUsed() != mem) {
		    if ((xmlMemUsed() != mem) &&
		        (extraMemoryFromResolver == 0)) {
			fprintf(stderr, "File %s leaked %d bytes\n",
				globbuf.gl_pathv[i], xmlMemUsed() - mem);
			nb_leaks++;
			err++;
		    }
		}
		testErrorsSize = 0;
	    }
	    if (result)
		free(result);
	    if (error)
		free(error);
	}
	globfree(&globbuf);
    } else {
        testErrorsSize = 0;
	testErrors[0] = 0;
	extraMemoryFromResolver = 0;
        res = tst->func(NULL, NULL, NULL, tst->options);
	if (res != 0) {
	    nb_errors++;
	    err++;
	}
    }
    return(err);
}
