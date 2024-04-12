void Com_TouchMemory( void ) {
	int		start, end;
	int		i, j;
	int		sum;
	memblock_t	*block;

	Z_CheckHeap();

	start = Sys_Milliseconds();

	sum = 0;

	j = hunk_low.permanent >> 2;
	for ( i = 0 ; i < j ; i+=64 ) {			// only need to touch each page
		sum += ((int *)s_hunkData)[i];
	}

	i = ( s_hunkTotal - hunk_high.permanent ) >> 2;
	j = hunk_high.permanent >> 2;
	for (  ; i < j ; i+=64 ) {			// only need to touch each page
		sum += ((int *)s_hunkData)[i];
	}

	for (block = mainzone->blocklist.next ; ; block = block->next) {
		if ( block->tag ) {
			j = block->size >> 2;
			for ( i = 0 ; i < j ; i+=64 ) {				// only need to touch each page
				sum += ((int *)block)[i];
			}
		}
		if ( block->next == &mainzone->blocklist ) {
			break;			// all blocks have been hit	
		}
	}

	end = Sys_Milliseconds();

	Com_Printf( "Com_TouchMemory: %i msec\n", end - start );
}
