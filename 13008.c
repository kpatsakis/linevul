add_cipher_name_to_ary(const OBJ_NAME *name, VALUE ary)
{
    rb_ary_push(ary, rb_str_new2(name->name));
    return NULL;
}
