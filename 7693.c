AudioRendererHost::AudioEntry* AudioRendererHost::LookupById(int stream_id) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));

  AudioEntryMap::iterator i = audio_entries_.find(stream_id);
  if (i != audio_entries_.end() && !i->second->pending_close)
    return i->second;
  return NULL;
}
