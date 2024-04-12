NPError NPN_GetURL(NPP id, const char* url, const char* target) {

   return GetURLNotify(id, url, target, false, 0);
 }
