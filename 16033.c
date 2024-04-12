static void FLTReplacePropertyName(FilterEncodingNode *psFilterNode,
                                   const char *pszOldName,
                                   const char *pszNewName)
{
  if (psFilterNode && pszOldName && pszNewName) {
    if (psFilterNode->eType == FILTER_NODE_TYPE_PROPERTYNAME) {
      if (psFilterNode->pszValue &&
          strcasecmp(psFilterNode->pszValue, pszOldName) == 0) {
        msFree(psFilterNode->pszValue);
        psFilterNode->pszValue = msStrdup(pszNewName);
      }
    }
    if (psFilterNode->psLeftNode)
      FLTReplacePropertyName(psFilterNode->psLeftNode, pszOldName,
                             pszNewName);
    if (psFilterNode->psRightNode)
      FLTReplacePropertyName(psFilterNode->psRightNode, pszOldName,
                             pszNewName);
  }
}
