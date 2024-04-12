AddFragment(struct xorg_list *frags, int bytes)
{
    FragmentList *f = malloc(sizeof(FragmentList) + bytes);
    if (!f) {
        return NULL;
    } else {
        f->bytes = bytes;
        xorg_list_add(&f->l, frags->prev);
        return (char*) f + sizeof(*f);
    }
}
