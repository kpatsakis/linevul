ofputil_uninit_tlv_table(struct ovs_list *mappings)
{
    struct ofputil_tlv_map *map;

    LIST_FOR_EACH_POP (map, list_node, mappings) {
        free(map);
    }
}
