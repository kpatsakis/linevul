struct json_tokener* json_tokener_new(void)
{
  return json_tokener_new_ex(JSON_TOKENER_DEFAULT_DEPTH);
}
