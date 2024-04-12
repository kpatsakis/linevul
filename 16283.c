int Huff_Receive (node_t *node, int *ch, byte *fin) {
	while (node && node->symbol == INTERNAL_NODE) {
		if (get_bit(fin)) {
			node = node->right;
		} else {
			node = node->left;
		}
	}
	if (!node) {
		return 0;
	}
	return (*ch = node->symbol);
 }
