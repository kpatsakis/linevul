NTSTATUS TCWriteRegistryKey (PUNICODE_STRING keyPath, wchar_t *keyValueName, ULONG keyValueType, void *valueData, ULONG valueSize)
{
	OBJECT_ATTRIBUTES regObjAttribs;
	HANDLE regKeyHandle;
	NTSTATUS status;
	UNICODE_STRING valName;

	InitializeObjectAttributes (&regObjAttribs, keyPath, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);
	status = ZwOpenKey (&regKeyHandle, KEY_READ | KEY_WRITE, &regObjAttribs);
	if (!NT_SUCCESS (status))
		return status;

	RtlInitUnicodeString (&valName, keyValueName);

	status = ZwSetValueKey (regKeyHandle, &valName, 0, keyValueType, valueData, valueSize);

	ZwClose (regKeyHandle);
	return status;
}
