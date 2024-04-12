static int bin_pe_init_tls(struct PE_(r_bin_pe_obj_t)* bin) {
	PE_(image_tls_directory) * image_tls_directory;
	PE_(image_data_directory) * data_dir_tls = &bin->data_directory[PE_IMAGE_DIRECTORY_ENTRY_TLS];
	PE_DWord tls_paddr = bin_pe_rva_to_paddr (bin, data_dir_tls->VirtualAddress);

	image_tls_directory = R_NEW0 (PE_(image_tls_directory));
	if (r_buf_read_at (bin->b, tls_paddr, (ut8*) image_tls_directory, sizeof (PE_(image_tls_directory))) != sizeof (PE_(image_tls_directory))) {
		bprintf ("Warning: read (image_tls_directory)\n");
		free (image_tls_directory);
		return 0;
	}
	bin->tls_directory = image_tls_directory;
	if (!image_tls_directory->AddressOfCallBacks) {
		return 0;
	}
	if (image_tls_directory->EndAddressOfRawData < image_tls_directory->StartAddressOfRawData) {
		return 0;
	}
	PE_DWord callbacks_paddr = bin_pe_rva_to_paddr (bin, bin_pe_va_to_rva (bin,
			(PE_DWord) image_tls_directory->AddressOfCallBacks));
	bin_pe_store_tls_callbacks (bin, callbacks_paddr);
	return 0;
}
