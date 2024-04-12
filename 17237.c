   bool IsNull(base::DictionaryValue* value, const std::string& key) {
     base::Value* child = NULL;
     if (!value->Get(key, &child)) {
      ADD_FAILURE();
      return false;
    }
    return child->GetType() == base::Value::TYPE_NULL;
  }
