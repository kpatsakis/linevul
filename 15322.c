static inline pvc_device* find_pvc(hdlc_device *hdlc, u16 dlci)
{
	pvc_device *pvc = state(hdlc)->first_pvc;

	while (pvc) {
		if (pvc->dlci == dlci)
			return pvc;
		if (pvc->dlci > dlci)
			return NULL; /* the list is sorted */
		pvc = pvc->next;
	}

	return NULL;
}
