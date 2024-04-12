    StateBase* doSerializeArrayBuffer(v8::Handle<v8::Value> arrayBuffer, StateBase* next)
    {
        return doSerialize(arrayBuffer, next);
    }
