  static void WaitForDeletion(
      scoped_refptr<ServiceWorkerRegistration> registration,
      base::OnceClosure callback) {
    DCHECK(!registration->is_deleted());
    registration->AddListener(
        new RegistrationDeletionListener(registration, std::move(callback)));
  }
