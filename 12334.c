static void nci_add_new_target(struct nci_dev *ndev,
			       struct nci_rf_discover_ntf *ntf)
{
	struct nfc_target *target;
	int i, rc;

	for (i = 0; i < ndev->n_targets; i++) {
		target = &ndev->targets[i];
		if (target->logical_idx == ntf->rf_discovery_id) {
			/* This target already exists, add the new protocol */
			nci_add_new_protocol(ndev, target, ntf->rf_protocol,
					     ntf->rf_tech_and_mode,
					     &ntf->rf_tech_specific_params);
			return;
		}
	}

	/* This is a new target, check if we've enough room */
	if (ndev->n_targets == NCI_MAX_DISCOVERED_TARGETS) {
		pr_debug("not enough room, ignoring new target...\n");
		return;
	}

	target = &ndev->targets[ndev->n_targets];

	rc = nci_add_new_protocol(ndev, target, ntf->rf_protocol,
				  ntf->rf_tech_and_mode,
				  &ntf->rf_tech_specific_params);
	if (!rc) {
		target->logical_idx = ntf->rf_discovery_id;
		ndev->n_targets++;

		pr_debug("logical idx %d, n_targets %d\n", target->logical_idx,
			 ndev->n_targets);
	}
}
