__docbDefaultSAXHandler(void) {
    if (IS_MAIN_THREAD)
	return (&docbDefaultSAXHandler);
    else
	return (&xmlGetGlobalState()->docbDefaultSAXHandler);
}
