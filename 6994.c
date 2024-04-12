long FS_FOpenFileReadDir(const char *filename, searchpath_t *search, fileHandle_t *file, qboolean uniqueFILE, qboolean unpure)
{
	long			hash;
	pack_t		*pak;
	fileInPack_t	*pakFile;
	directory_t	*dir;
	char		*netpath;
	FILE		*filep;
	int			len;

	if(filename == NULL)
		Com_Error(ERR_FATAL, "FS_FOpenFileRead: NULL 'filename' parameter passed");

	if(filename[0] == '/' || filename[0] == '\\')
		filename++;

	if(strstr(filename, ".." ) || strstr(filename, "::"))
	{
	        if(file == NULL)
	                return qfalse;
	                
		*file = 0;
		return -1;
	}
        
	if(com_fullyInitialized && strstr(filename, "rtcwkey"))
	{
	        if(file == NULL)
	                return qfalse;

		*file = 0;
		return -1;
	}

	if(file == NULL)
	{

		if(search->pack)
		{
			hash = FS_HashFileName(filename, search->pack->hashSize);
                        
                        if(search->pack->hashTable[hash] && !(fs_filter_flag & FS_EXCLUDE_PK3))
                        {
				pak = search->pack;
				pakFile = pak->hashTable[hash];

				do
				{
					if(!FS_FilenameCompare(pakFile->name, filename))
					{
						if(pakFile->len)
        						return pakFile->len;
                                                else
                                                {
                                                        return 1;
                                                }
					}

					pakFile = pakFile->next;
				} while(pakFile != NULL);
			}
		}
		else if(search->dir && !(fs_filter_flag & FS_EXCLUDE_DIR))
		{
			dir = search->dir;
		
			netpath = FS_BuildOSPath(dir->path, dir->gamedir, filename);
			filep = Sys_FOpen(netpath, "rb");

			if(filep)
			{
			        len = FS_fplength(filep);
				fclose(filep);
				
				if(len)
        				return len;
                                else
                                        return 1;
			}
		}
		
		return 0;
	}

	*file = FS_HandleForFile();
	fsh[*file].handleFiles.unique = uniqueFILE;
	
	if(search->pack)
	{
		hash = FS_HashFileName(filename, search->pack->hashSize);

		if(search->pack->hashTable[hash] && !(fs_filter_flag & FS_EXCLUDE_PK3))
		{
			if(!unpure && !FS_PakIsPure(search->pack))
			{
				*file = 0;
				return -1;
			}

			pak = search->pack;
			pakFile = pak->hashTable[hash];
		
			do
			{
				if(!FS_FilenameCompare(pakFile->name, filename))
				{

					len = strlen(filename);

					if (!(pak->referenced & FS_GENERAL_REF))
					{
						if(!FS_IsExt(filename, ".shader", len) &&
						   !FS_IsExt(filename, ".txt", len) &&
						   !FS_IsExt(filename, ".cfg", len) &&
						   !FS_IsExt(filename, ".config", len) &&
						   !FS_IsExt(filename, ".bot", len) &&
						   !FS_IsExt(filename, ".arena", len) &&
						   !FS_IsExt(filename, ".menu", len) &&
						   !strstr(filename, "levelshots"))
						{
							pak->referenced |= FS_GENERAL_REF;
						}
					}

					if(strstr(filename, Sys_GetDLLName( "cgame" )))
						pak->referenced |= FS_CGAME_REF;

					if(strstr(filename, Sys_GetDLLName( "ui" )))
						pak->referenced |= FS_UI_REF;

					if(strstr(filename, "cgame.mp.qvm"))
						pak->referenced |= FS_CGAME_REF;

					if(strstr(filename, "ui.mp.qvm"))
						pak->referenced |= FS_UI_REF;

					if ( Q_stricmp( filename + len - 4, ".bsp" ) == 0 &&
						 Q_stricmp( pak->pakBasename, "pak0" ) == 0 ) {

						*file = 0;
						return -1;
					}

					if(uniqueFILE)
					{
						fsh[*file].handleFiles.file.z = unzOpen(pak->pakFilename);
					
						if(fsh[*file].handleFiles.file.z == NULL)
							Com_Error(ERR_FATAL, "Couldn't open %s", pak->pakFilename);
					}
					else
						fsh[*file].handleFiles.file.z = pak->handle;

					Q_strncpyz(fsh[*file].name, filename, sizeof(fsh[*file].name));
					fsh[*file].zipFile = qtrue;
				
					unzSetOffset(fsh[*file].handleFiles.file.z, pakFile->pos);

					unzOpenCurrentFile(fsh[*file].handleFiles.file.z);
					fsh[*file].zipFilePos = pakFile->pos;
					fsh[*file].zipFileLen = pakFile->len;

					if(fs_debug->integer)
					{
						Com_Printf("FS_FOpenFileRead: %s (found in '%s')\n", 
							filename, pak->pakFilename);
					}
				
					return pakFile->len;
				}
			
				pakFile = pakFile->next;
			} while(pakFile != NULL);
		}
	}
	else if(search->dir && !(fs_filter_flag & FS_EXCLUDE_DIR))
	{

		len = strlen(filename);
		if(!unpure && fs_numServerPaks)
		{
			if(!FS_IsExt(filename, ".cfg", len) &&		// for config files
			   !FS_IsExt(filename, ".menu", len) &&		// menu files
			   !FS_IsExt(filename, ".game", len) &&		// menu files
			   !FS_IsExt(filename, ".dat", len) &&		// for journal files
			   !FS_IsDemoExt(filename, len))			// demos
			{
				*file = 0;
				return -1;
			}
		}

		dir = search->dir;

		netpath = FS_BuildOSPath(dir->path, dir->gamedir, filename);
		filep = Sys_FOpen(netpath, "rb");

		if (filep == NULL)
		{
			*file = 0;
                        return -1;
		}

		Q_strncpyz(fsh[*file].name, filename, sizeof(fsh[*file].name));
		fsh[*file].zipFile = qfalse;
		
		if(fs_debug->integer)
		{
			Com_Printf("FS_FOpenFileRead: %s (found in '%s%c%s')\n", filename,
				dir->path, PATH_SEP, dir->gamedir);
		}

		fsh[*file].handleFiles.file.o = filep;
		return FS_fplength(filep);
	}

	*file = 0;
	return -1;
}
