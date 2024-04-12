void FS_ClearPakReferences( int flags ) {
	searchpath_t *search;

	if ( !flags ) {
		flags = -1;
	}
	for ( search = fs_searchpaths; search; search = search->next ) {
		if ( search->pack ) {
			search->pack->referenced &= ~flags;
		}
	}
}
