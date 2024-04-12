xmlRecoverDoc(const xmlChar *cur) {
    return(xmlSAXParseDoc(NULL, cur, 1));
}
