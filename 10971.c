void WorkerThread::terminateAndWait()
{
    stop();
    m_terminationEvent->wait();
}
