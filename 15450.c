xmlXPtrLocationSetMerge(xmlLocationSetPtr val1, xmlLocationSetPtr val2) {
    int i;

    if (val1 == NULL) return(NULL);
    if (val2 == NULL) return(val1);

    /*
     * !!!!! this can be optimized a lot, knowing that both
     *       val1 and val2 already have unicity of their values.
     */

    for (i = 0;i < val2->locNr;i++)
        xmlXPtrLocationSetAdd(val1, val2->locTab[i]);

    return(val1);
}
