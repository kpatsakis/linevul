void comps_objmrtree_data_destroy(COMPS_ObjMRTreeData * rtd) {
    free(rtd->key);
    COMPS_OBJECT_DESTROY(rtd->data);
    comps_hslist_destroy(&rtd->subnodes);
    free(rtd);
}
