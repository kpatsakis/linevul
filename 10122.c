ReadUserLogFileState::convertState(
	const ReadUserLog::FileState				&state,
	const ReadUserLogFileState::FileStatePub	*&pub )
{
	pub = (const ReadUserLogFileState::FileStatePub *) state.buf;
	return true;
}
