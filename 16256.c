void Smb4KGlobal::clearHostsList()
{
  mutex.lock();

  while ( !p->hostsList.isEmpty() )
  {
    delete p->hostsList.takeFirst();
  }

  mutex.unlock();
}
