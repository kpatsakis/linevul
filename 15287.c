std::string ASF_LegacyManager::GetField ( fieldType field )
{
	if ( field >= fieldLast ) return std::string();
	return fields[field];
}
