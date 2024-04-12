bool roleAllowsModal(AccessibilityRole role) {
  return role == DialogRole || role == AlertDialogRole;
}
