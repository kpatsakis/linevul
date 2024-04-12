 static inline BOOLEAN guid_eq(const GUID *guid1, const GUID *guid2) {
 	if ((guid1 != NULL) && (guid2 != NULL)) {
		return (memcmp(guid1, guid2, sizeof(GUID)) == 0);
	}
	return false;
}
