SafeSock::my_ip_str()
{

	if(_state != sock_connect) {
		dprintf(D_ALWAYS,"ERROR: SafeSock::sender_ip_str() called on socket tht is not in connected state\n");
		return NULL;
	}

	if(_my_ip_buf[0]) {
		return _my_ip_buf;
	}

	SafeSock s;
	s.bind(true);

	if (s._state != sock_bound) {
		dprintf(D_ALWAYS,
		        "SafeSock::my_ip_str() failed to bind: _state = %d\n",
			  s._state); 
		return NULL;
	}

	if (condor_connect(s._sock, _who) != 0) {
#if defined(WIN32)
		int lasterr = WSAGetLastError();
		dprintf( D_ALWAYS, "SafeSock::my_ip_str() failed to connect, errno = %d\n",
				 lasterr );
#else
		dprintf( D_ALWAYS, "SafeSock::my_ip_str() failed to connect, errno = %d\n",
				 errno );
#endif
		return NULL;
	}

	condor_sockaddr addr;
	addr = s.my_addr();
	strcpy(_my_ip_buf, addr.to_ip_string().Value());
	return _my_ip_buf;
}
