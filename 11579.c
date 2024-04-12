crm_xml_replace(xmlNode * node, const char *name, const char *value)
{
    bool dirty = FALSE;
    xmlAttr *attr = NULL;
    const char *old_value = NULL;

    CRM_CHECK(node != NULL, return NULL);
    CRM_CHECK(name != NULL && name[0] != 0, return NULL);

    old_value = crm_element_value(node, name);

    /* Could be re-setting the same value */
    CRM_CHECK(old_value != value, return value);

    if(__xml_acl_check(node, name, xpf_acl_write) == FALSE) {
        /* Create a fake object linked to doc->_private instead? */
        crm_trace("Cannot replace %s=%s to %s", name, value, node->name);
        return NULL;

    } else if (old_value != NULL && value == NULL) {
        xml_remove_prop(node, name);
        return NULL;

    } else if (value == NULL) {
        return NULL;
    }

    if(TRACKING_CHANGES(node)) {
        if(old_value == NULL || value == NULL || strcmp(old_value, value) != 0) {
            dirty = TRUE;
        }
    }

    attr = xmlSetProp(node, (const xmlChar *)name, (const xmlChar *)value);
    if(dirty) {
        crm_attr_dirty(attr);
    }
    CRM_CHECK(attr && attr->children && attr->children->content, return NULL);
    return (char *)attr->children->content;
}
