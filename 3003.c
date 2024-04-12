static RList * get_java_bin_obj_list(RAnal *anal) {
	RBinJavaObj *bin_obj = (RBinJavaObj * )get_java_bin_obj(anal);
	return  r_bin_java_get_bin_obj_list_thru_obj (bin_obj);
}
