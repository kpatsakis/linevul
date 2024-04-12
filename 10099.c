__xmlIndentTreeOutput(void) {
    if (IS_MAIN_THREAD)
	return (&xmlIndentTreeOutput);
    else
	return (&xmlGetGlobalState()->xmlIndentTreeOutput);
}
