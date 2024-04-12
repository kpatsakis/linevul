static void derive_permissions_recursive_locked(struct fuse* fuse, struct node *parent) {
 struct node *node;
 for (node = parent->child; node; node = node->next) {
        derive_permissions_locked(fuse, parent, node);
 if (node->child) {
            derive_permissions_recursive_locked(fuse, node);
 }
 }
}
