PHP_MINFO_FUNCTION(bcmath)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "BCMath support", "enabled");
	php_info_print_table_end();
	DISPLAY_INI_ENTRIES();
}
