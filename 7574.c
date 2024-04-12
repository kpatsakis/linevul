bool Smb4KGlobal::removeShare( Smb4KShare *share )
{
  Q_ASSERT( share );

  bool removed = false;

  mutex.lock();

  int index = p->sharesList.indexOf( share );

  if ( index != -1 )
  {
    delete p->sharesList.takeAt( index );
    removed = true;
  }
  else
  {
    Smb4KShare *s = findShare( share->shareName(), share->hostName(), share->workgroupName() );

    if ( s )
    {
      index = p->sharesList.indexOf( s );

      if ( index != -1 )
      {
        delete p->sharesList.takeAt( index );
        removed = true;
      }
      else
      {
      }
    }
    else
    {
    }

    delete share;
  }

  mutex.unlock();

  return removed;
}
