print_node_summary(pe_working_set_t * data_set, gboolean operations)
{
    xmlNode *lrm_rsc = NULL;
    xmlNode *rsc_entry = NULL;
    xmlNode *node_state = NULL;
    xmlNode *cib_status = get_object_root(XML_CIB_TAG_STATUS, data_set->input);

    if (operations) {
        print_as("\nOperations:\n");
    } else {
        print_as("\nMigration summary:\n");
    }

    for (node_state = __xml_first_child(cib_status); node_state != NULL;
         node_state = __xml_next(node_state)) {
        if (crm_str_eq((const char *)node_state->name, XML_CIB_TAG_STATE, TRUE)) {
            node_t *node = pe_find_node_id(data_set->nodes, ID(node_state));

            if (node == NULL || node->details->online == FALSE) {
                continue;
            }

            print_as("* Node %s: ", crm_element_value(node_state, XML_ATTR_UNAME));
            print_as("\n");

            lrm_rsc = find_xml_node(node_state, XML_CIB_TAG_LRM, FALSE);
            lrm_rsc = find_xml_node(lrm_rsc, XML_LRM_TAG_RESOURCES, FALSE);

            for (rsc_entry = __xml_first_child(lrm_rsc); rsc_entry != NULL;
                 rsc_entry = __xml_next(rsc_entry)) {
                if (crm_str_eq((const char *)rsc_entry->name, XML_LRM_TAG_RESOURCE, TRUE)) {
                    if (operations) {
                        print_rsc_history(data_set, node, rsc_entry);

                    } else {
                        const char *rsc_id = crm_element_value(rsc_entry, XML_ATTR_ID);
                        resource_t *rsc = pe_find_resource(data_set->resources, rsc_id);

                        if (rsc) {
                            print_rsc_summary(data_set, node, rsc, FALSE);
                        } else {
                            print_as("   %s: orphan\n", rsc_id);
                        }
                    }
                }
            }
        }
    }
}
