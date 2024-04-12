FileTransfer::HandleCommands(Service *, int command, Stream *s)
{
	FileTransfer *transobject;
	char *transkey = NULL;

	dprintf(D_FULLDEBUG,"entering FileTransfer::HandleCommands\n");

	if ( s->type() != Stream::reli_sock ) {
		return 0;
	}
	ReliSock *sock = (ReliSock *) s;

	sock->timeout(0);

	if (!sock->get_secret(transkey) ||
		!sock->end_of_message() ) {
		dprintf(D_FULLDEBUG,
			    	"FileTransfer::HandleCommands failed to read transkey\n");
		return 0;
	}
	dprintf(D_FULLDEBUG,
					"FileTransfer::HandleCommands read transkey=%s\n",transkey);

	MyString key(transkey);
	free(transkey);
	if ( (TranskeyTable == NULL) || 
		 (TranskeyTable->lookup(key,transobject) < 0) ) {		
		sock->snd_int(0,1);	// sends a "0" then an end_of_record
		dprintf(D_FULLDEBUG,"transkey is invalid!\n");
		sleep(5);
		return FALSE;
	}

	switch (command) {
		case FILETRANS_UPLOAD:
			{
			const char *currFile;
			transobject->CommitFiles();
			Directory spool_space( transobject->SpoolSpace, 
								   transobject->getDesiredPrivState() );
			while ( (currFile=spool_space.Next()) ) {
				if (transobject->UserLogFile && 
						!file_strcmp(transobject->UserLogFile,currFile)) 
				{
					continue;
				} else {
					const char *filename = spool_space.GetFullPath();
					if ( !transobject->InputFiles->file_contains(filename) &&
						 !transobject->InputFiles->file_contains(condor_basename(filename)) ) {
						transobject->InputFiles->append(filename);
					}
				}
			}
			transobject->FilesToSend = transobject->InputFiles;
			transobject->EncryptFiles = transobject->EncryptInputFiles;
			transobject->DontEncryptFiles = transobject->DontEncryptInputFiles;
			transobject->Upload(sock,true);		// blocking = true for now...
			}
			break;
		case FILETRANS_DOWNLOAD:
			transobject->Download(sock,true);	// blocking = true for now...
			break;
		default:
			dprintf(D_ALWAYS,
				"FileTransfer::HandleCommands: unrecognized command %d\n",
				command);
			return 0;
			break;
	}

	return 1;
}
