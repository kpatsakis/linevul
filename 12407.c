bool AllSamplesPassedQuery::End(base::subtle::Atomic32 submit_count) {
  EndQueryHelper(target());
  return AddToPendingQueue(submit_count);
}
