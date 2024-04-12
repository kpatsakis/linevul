int SearchMLUEntry(cmsMLU* mlu, cmsUInt16Number LanguageCode, cmsUInt16Number CountryCode)
{
    int i;

    if (mlu == NULL) return -1;

    for (i=0; i < mlu ->UsedEntries; i++) {

        if (mlu ->Entries[i].Country  == CountryCode &&
            mlu ->Entries[i].Language == LanguageCode) return i;
    }

    return -1;
}
