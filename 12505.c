void Smb4KGlobal::openShare( Smb4KShare *share, OpenWith openWith )
{
  if ( !share || share->isInaccessible() )
  {
    return;
  }

  switch ( openWith )
  {
    case FileManager:
    {
      KUrl url;
      url.setPath( share->canonicalPath() );

      (void) new KRun( url, 0, 0, true );

      break;
    }
    case Konsole:
    {
      QString konsole = KGlobal::dirs()->findResource( "exe", "konsole" );

      if ( konsole.isEmpty() )
      {
        Smb4KNotification::commandNotFound("konsole");
      }
      else
      {
        KRun::runCommand( konsole+" --workdir "+KShell::quoteArg( share->canonicalPath() ), 0 );
      }

      break;
    }
    default:
    {
      break;
    }
  }
}
