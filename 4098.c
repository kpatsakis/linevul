parity_next (int parity)
{
	switch(parity) {
	case P_NONE:
		parity = P_EVEN;
		break;
	case P_EVEN:
		parity = P_ODD;
		break;
	case P_ODD:
		parity = P_NONE;
		break;
	default:
		parity = P_NONE;
		break;
	}

	return parity;
}
