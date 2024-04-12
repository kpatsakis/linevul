void AppendAvailableAutocompletion(int type,
                                   int count,
                                   std::string* autocompletions) {
  if (!autocompletions->empty())
    autocompletions->append("j");
  base::StringAppendF(autocompletions, "%d", type);
  if (count > 1)
    base::StringAppendF(autocompletions, "l%d", count);
}
