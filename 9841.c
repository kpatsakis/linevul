PrintingContext::Result PrintingContextCairo::NewDocument(
    const string16& document_name) {
  DCHECK(!in_print_job_);
  in_print_job_ = true;

#if !defined(OS_CHROMEOS)
  document_name_ = document_name;
#endif  // !defined(OS_CHROMEOS)

  return OK;
}
