static int cmp_gss_krb5_name(kadm5_server_handle_t handle,
                             gss_name_t gss_name, krb5_principal princ)
{
    krb5_principal princ2;
    int status;

    if (! gss_to_krb5_name(handle, gss_name, &princ2))
        return 0;
    status = krb5_principal_compare(handle->context, princ, princ2);
    krb5_free_principal(handle->context, princ2);
    return status;
}
