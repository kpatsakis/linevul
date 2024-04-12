int SetThreadName(const std::thread::native_handle_type &thread, const char* threadName) {
	DWORD dwThreadID = ::GetThreadId( static_cast<HANDLE>( thread ) );
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = threadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;
#pragma warning(push)
#pragma warning(disable: 6320 6322)
	__try{
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except (EXCEPTION_EXECUTE_HANDLER){
	}
#pragma warning(pop)
	return 0;
}
