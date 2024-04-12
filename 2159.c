status_t NuPlayer::GenericSource::seekTo(int64_t seekTimeUs) {
    sp<AMessage> msg = new AMessage(kWhatSeek, this);
    msg->setInt64("seekTimeUs", seekTimeUs);

    sp<AMessage> response;
 status_t err = msg->postAndAwaitResponse(&response);
 if (err == OK && response != NULL) {
        CHECK(response->findInt32("err", &err));
 }

 return err;
}
