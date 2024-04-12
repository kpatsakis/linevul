void DupTagTypeList(struct _cmsContext_struct* ctx, 
                    const struct _cmsContext_struct* src, 
                    int loc)
{
   _cmsTagTypePluginChunkType newHead = { NULL };
   _cmsTagTypeLinkedList*  entry;
   _cmsTagTypeLinkedList*  Anterior = NULL;
   _cmsTagTypePluginChunkType* head = (_cmsTagTypePluginChunkType*) src->chunks[loc];

   for (entry = head->TagTypes;
       entry != NULL;
       entry = entry ->Next) {

           _cmsTagTypeLinkedList *newEntry = ( _cmsTagTypeLinkedList *) _cmsSubAllocDup(ctx ->MemPool, entry, sizeof(_cmsTagTypeLinkedList));

           if (newEntry == NULL) 
               return;

           newEntry -> Next = NULL;
           if (Anterior)
               Anterior -> Next = newEntry;

           Anterior = newEntry;

           if (newHead.TagTypes == NULL)
               newHead.TagTypes = newEntry;
   }

   ctx ->chunks[loc] = _cmsSubAllocDup(ctx->MemPool, &newHead, sizeof(_cmsTagTypePluginChunkType));
}
