CopyKeyNamesToKeymap(struct xkb_keymap *keymap, KeyNamesInfo *info)
{
    struct xkb_key *keys;
    xkb_keycode_t min_key_code, max_key_code, kc;

    min_key_code = info->min_key_code;
    max_key_code = info->max_key_code;
    /* If the keymap has no keys, let's just use the safest pair we know. */
    if (min_key_code == XKB_KEYCODE_INVALID) {
        min_key_code = 8;
        max_key_code = 255;
    }

    keys = calloc(max_key_code + 1, sizeof(*keys));
    if (!keys)
        return false;

    for (kc = min_key_code; kc <= max_key_code; kc++)
        keys[kc].keycode = kc;

    for (kc = info->min_key_code; kc <= info->max_key_code; kc++)
        keys[kc].name = darray_item(info->key_names, kc);

    keymap->min_key_code = min_key_code;
    keymap->max_key_code = max_key_code;
    keymap->keys = keys;
    return true;
}
