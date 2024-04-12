std::unique_ptr<base::trace_event::TracedValue> ShellSurface::AsTracedValue()
    const {
  std::unique_ptr<base::trace_event::TracedValue> value(
      new base::trace_event::TracedValue());
  value->SetString("title", base::UTF16ToUTF8(title_));
  value->SetString("application_id", application_id_);
  return value;
}
