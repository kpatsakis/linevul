static int empty(Renode *node)
{
	if (!node) return 1;
	switch (node->type) {
	default: return 1;
	case P_CAT: return empty(node->x) && empty(node->y);
	case P_ALT: return empty(node->x) || empty(node->y);
	case P_REP: return empty(node->x) || node->m == 0;
	case P_PAR: return empty(node->x);
	case P_REF: return empty(node->x);
	case P_ANY: case P_CHAR: case P_CCLASS: case P_NCCLASS: return 0;
	}
}
