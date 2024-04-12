static void DeleteSession( SESSION *session )
{
    SESSION_LIST_ENTRY *predSession;
    void *newNextEntry;

    if( session == &local_sessions_list->session )
        local_sessions_list = 0;
    else
    {
        for( predSession = local_sessions_list;
                predSession != 0 && &( ( ( SESSION_LIST_ENTRY *)predSession->nextEntry )->session ) != session;
                predSession = predSession->nextEntry )
            ;

        if( predSession != 0 )
        {
            local_session_entries_used--;

            newNextEntry = &( (SESSION_LIST_ENTRY *)predSession->nextEntry)->nextEntry;

            free( predSession->nextEntry );

            predSession->nextEntry = newNextEntry;
        }
    }
}
