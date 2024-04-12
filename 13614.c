ReadUserLogFileState::convertState(
	const ReadUserLog::FileState			&state,
	const ReadUserLogFileState::FileState	*&internal )
{
	const ReadUserLogFileState::FileStatePub	*pub;
	convertState(state, pub);
	internal = &(pub->internal);
	return true;
}
