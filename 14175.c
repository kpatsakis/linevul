void ClrFormatPromptHook(void) {
	UnhookWinEvent(fp_weh);
	fp_weh = NULL;
}
