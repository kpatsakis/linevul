void RenderThread::RemoveObserver(RenderProcessObserver* observer) {
  observers_.RemoveObserver(observer);
}
