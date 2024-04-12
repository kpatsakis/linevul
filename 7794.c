  virtual void SetUp() {
    dir_maker_.SetUp();
    mock_server_.reset(new MockConnectionManager(directory()));
    EnableDatatype(syncable::BOOKMARKS);
    EnableDatatype(syncable::NIGORI);
    EnableDatatype(syncable::PREFERENCES);
    EnableDatatype(syncable::NIGORI);
    worker_ = new FakeModelWorker(GROUP_PASSIVE);
    std::vector<SyncEngineEventListener*> listeners;
    listeners.push_back(this);
    context_.reset(
        new SyncSessionContext(
            mock_server_.get(), directory(), this,
            &extensions_activity_monitor_, listeners, NULL,
            &traffic_recorder_));
    ASSERT_FALSE(context_->resolver());
    syncer_ = new Syncer();
    session_.reset(MakeSession());

    ReadTransaction trans(FROM_HERE, directory());
    syncable::Directory::ChildHandles children;
    directory()->GetChildHandlesById(&trans, trans.root_id(), &children);
    ASSERT_EQ(0u, children.size());
    saw_syncer_event_ = false;
    root_id_ = TestIdFactory::root();
    parent_id_ = ids_.MakeServer("parent id");
    child_id_ = ids_.MakeServer("child id");
  }
