void IRCView::dropEvent(QDropEvent* e)
{
    if (e->mimeData() && e->mimeData()->hasUrls())
        emit urlsDropped(KUrl::List::fromMimeData(e->mimeData(), KUrl::List::PreferLocalUrls));
}
