static void RunCopyCallbackOnMainThread(scoped_ptr<CopyOutputRequest> request,
                                        scoped_ptr<CopyOutputResult> result) {
  request->SendResult(result.Pass());
}
