void comps_objmrtree_set_x(COMPS_ObjMRTree *rt, char *key, COMPS_Object *data) {
    __comps_objmrtree_set(rt, key, strlen(key), data);
}
