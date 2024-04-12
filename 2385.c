void PrintJobWorker::GetSettingsDone(PrintingContext::Result result) {


  owner_->PostTask(FROM_HERE,
                   base::Bind(&PrintJobWorkerOwner::GetSettingsDone,
                              make_scoped_refptr(owner_),
                              printing_context_->settings(),
                              result));
}
