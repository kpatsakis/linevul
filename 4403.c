int parse_boolean(const char *v) {
        assert(v);

        if (streq(v, "1") || v[0] == 'y' || v[0] == 'Y' || v[0] == 't' || v[0] == 'T' || !strcasecmp(v, "on"))
                return 1;
        else if (streq(v, "0") || v[0] == 'n' || v[0] == 'N' || v[0] == 'f' || v[0] == 'F' || !strcasecmp(v, "off"))
                return 0;

        return -EINVAL;
}
