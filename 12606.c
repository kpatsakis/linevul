static int json_integer_equal(json_t *integer1, json_t *integer2)
{
    return json_integer_value(integer1) == json_integer_value(integer2);
}
