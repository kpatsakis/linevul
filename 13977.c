double json_real_value(const json_t *json)
{
    if(!json_is_real(json))
        return 0;

    return json_to_real(json)->value;
}
