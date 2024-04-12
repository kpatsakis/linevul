Document& Document::MasterDocument() const {
  if (!imports_controller_)
    return *const_cast<Document*>(this);

  Document* master = imports_controller_->Master();
  DCHECK(master);
  return *master;
}
