GetEntriesString(Entries *entries, char *str)
{
    Buffer buff;

    if (str && *str) {
	buff.buff = str;
	buff.used = strlen(str);
	GetEntries(entries, &buff, 1);
    }
}
