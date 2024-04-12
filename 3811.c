    DictionaryValue* ToValue() const {
      DictionaryValue* value = new DictionaryValue();
      value->SetInteger("totalCount", total_count);
      value->SetString("payload", payload);
      return value;
    }
