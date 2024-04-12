ofproto_normalize_type(const char *type)
{
    return type && type[0] ? type : "system";
}
