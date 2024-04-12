ScriptPromise ImageCapture::getPhotoCapabilities(ScriptState* script_state) {
  ScriptPromiseResolver* resolver = ScriptPromiseResolver::Create(script_state);
  ScriptPromise promise = resolver->Promise();

  if (!service_) {
    resolver->Reject(DOMException::Create(kNotFoundError, kNoServiceError));
    return promise;
  }
  service_requests_.insert(resolver);

  auto resolver_cb = WTF::Bind(&ImageCapture::ResolveWithPhotoCapabilities,
                               WrapPersistent(this));

  service_->GetPhotoState(
      stream_track_->Component()->Source()->Id(),
      ConvertToBaseCallback(WTF::Bind(
          &ImageCapture::OnMojoGetPhotoState, WrapPersistent(this),
          WrapPersistent(resolver), WTF::Passed(std::move(resolver_cb)),
          false /* trigger_take_photo */)));
  return promise;
}
