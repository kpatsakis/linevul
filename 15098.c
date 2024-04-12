xsmp_get_app_name (GsmClient *client)
{
        SmProp *prop;
        char   *name;

        prop = find_property (GSM_XSMP_CLIENT (client), SmProgram, NULL);
        name = prop_to_command (prop);

        return name;
}
