json_t *json_deep_copy(const json_t *json)
{
    if(!json)
        return NULL;

    if(json_is_object(json))
        return json_object_deep_copy(json);

    if(json_is_array(json))
        return json_array_deep_copy(json);

    /* for the rest of the types, deep copying doesn't differ from
       shallow copying */

    if(json_is_string(json))
        return json_string_copy(json);

    if(json_is_integer(json))
        return json_integer_copy(json);

    if(json_is_real(json))
        return json_real_copy(json);

    if(json_is_true(json) || json_is_false(json) || json_is_null(json))
        return (json_t *)json;

    return NULL;
}
