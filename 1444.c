kadm5_setkey_principal_3(void *server_handle,
                         krb5_principal principal,
                         krb5_boolean keepold,
                         int n_ks_tuple, krb5_key_salt_tuple *ks_tuple,
                         krb5_keyblock *keyblocks,
                         int n_keys)
{
    kadm5_key_data *key_data;
    kadm5_ret_t ret;
    int i;

    if (keyblocks == NULL)
        return EINVAL;

    if (n_ks_tuple) {
        if (n_ks_tuple != n_keys)
            return KADM5_SETKEY3_ETYPE_MISMATCH;
        for (i = 0; i < n_ks_tuple; i++) {
            if (ks_tuple[i].ks_enctype != keyblocks[i].enctype)
                return KADM5_SETKEY3_ETYPE_MISMATCH;
        }
    }

    key_data = calloc(n_keys, sizeof(kadm5_key_data));
    if (key_data == NULL)
        return ENOMEM;

    for (i = 0; i < n_keys; i++) {
        key_data[i].key = keyblocks[i];
        key_data[i].salt.type =
            n_ks_tuple ? ks_tuple[i].ks_salttype : KRB5_KDB_SALTTYPE_NORMAL;
    }

    ret = kadm5_setkey_principal_4(server_handle, principal, keepold,
                                   key_data, n_keys);
    free(key_data);
    return ret;
}
