  TestConnectionHelper(base::TaskRunner* runner,
                       QuicClock* clock,
                       MockUDPClientSocket* socket)
      : QuicConnectionHelper(runner, clock, socket) {
  }
