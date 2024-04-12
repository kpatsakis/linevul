int FS_FindVM(void **startSearch, char *found, int foundlen, const char *name, int enableDll)
{
	searchpath_t *search, *lastSearch;
	directory_t *dir;
	pack_t *pack;
	char dllName[MAX_OSPATH], qvmName[MAX_OSPATH];
	char *netpath;

	if(!fs_searchpaths)
		Com_Error(ERR_FATAL, "Filesystem call made without initialization");

	if(enableDll)
		Q_strncpyz(dllName, Sys_GetDLLName(name), sizeof(dllName));

	Com_sprintf(qvmName, sizeof(qvmName), "vm/%s.sp.qvm", name);

	lastSearch = *startSearch;
	if(*startSearch == NULL)
		search = fs_searchpaths;
	else
		search = lastSearch->next;

	while(search)
	{
		if(search->dir && !fs_numServerPaks)
		{
			dir = search->dir;

			if(enableDll)
			{
				netpath = FS_BuildOSPath(dir->path, dir->gamedir, dllName);

				if(FS_FileInPathExists(netpath))
				{
					Q_strncpyz(found, netpath, foundlen);
					*startSearch = search;

					return VMI_NATIVE;
				}
			}

			if(FS_FOpenFileReadDir(qvmName, search, NULL, qfalse, qfalse) > 0)
			{
				*startSearch = search;
				return VMI_COMPILED;
			}
		}
		else if(search->pack)
		{
			pack = search->pack;

			if(lastSearch && lastSearch->pack)
			{

				if(!FS_FilenameCompare(lastSearch->pack->pakPathname, pack->pakPathname))
				{
					search = search->next;
					continue;
				}
			}

			if(FS_FOpenFileReadDir(qvmName, search, NULL, qfalse, qfalse) > 0)
			{
				*startSearch = search;

				return VMI_COMPILED;
			}
		}

		search = search->next;
	}

	return -1;
}
