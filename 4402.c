static bool nl80211_valid_auth_type(enum nl80211_auth_type auth_type)
{
	return auth_type <= NL80211_AUTHTYPE_MAX;
}
