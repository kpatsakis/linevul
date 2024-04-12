__xml_acl_apply(xmlNode *xml) 
{
    GListPtr aIter = NULL;
    xml_private_t *p = NULL;
    xmlXPathObjectPtr xpathObj = NULL;

    if(xml_acl_enabled(xml) == FALSE) {
        p = xml->doc->_private;
        crm_trace("Not applying ACLs for %s", p->user);
        return;
    }

    p = xml->doc->_private;
    for(aIter = p->acls; aIter != NULL; aIter = aIter->next) {
        int max = 0, lpc = 0;
        xml_acl_t *acl = aIter->data;

        xpathObj = xpath_search(xml, acl->xpath);
        max = numXpathResults(xpathObj);

        for(lpc = 0; lpc < max; lpc++) {
            xmlNode *match = getXpathResult(xpathObj, lpc);
            char *path = xml_get_path(match);

            p = match->_private;
            crm_trace("Applying %x to %s for %s", acl->mode, path, acl->xpath);

#ifdef SUSE_ACL_COMPAT
            if(is_not_set(p->flags, acl->mode)) {
                if(is_set(p->flags, xpf_acl_read)
                   || is_set(p->flags, xpf_acl_write)
                   || is_set(p->flags, xpf_acl_deny)) {
                    crm_config_warn("Configuration element %s is matched by multiple ACL rules, only the first applies ('%s' wins over '%s')",
                                    path, __xml_acl_to_text(p->flags), __xml_acl_to_text(acl->mode));
                    free(path);
                    continue;
                }
            }
#endif

            p->flags |= acl->mode;
            free(path);
        }
        crm_trace("Now enforcing ACL: %s (%d matches)", acl->xpath, max);
        freeXpathObject(xpathObj);
    }

    p = xml->_private;
    if(is_not_set(p->flags, xpf_acl_read) && is_not_set(p->flags, xpf_acl_write)) {
        p->flags |= xpf_acl_deny;
        p = xml->doc->_private;
        crm_info("Enforcing default ACL for %s to %s", p->user, crm_element_name(xml));
    }

}
