Smb4KMountJob::Smb4KMountJob( QObject *parent ) : KJob( parent ),
  m_started( false ), m_parent_widget( NULL ), m_processed( 0 )
{
  setCapabilities( KJob::Killable );
}
