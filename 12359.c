pseudo_get_user_info(ClassAd *&ad)
{
	static ClassAd* user_ad = NULL;


	if( ! user_ad ) {
		user_ad = new ClassAd;

#ifndef WIN32
		char buf[1024];

		sprintf( buf, "%s = %d", ATTR_UID, (int)get_user_uid() );
		user_ad->Insert( buf );

		sprintf( buf, "%s = %d", ATTR_GID, (int)get_user_gid() );
		user_ad->Insert( buf );
#endif

	}

	ad = user_ad;
	return 0;
}
