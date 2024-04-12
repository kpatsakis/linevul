proto_register_wbxml(void)
{
	module_t *wbxml_module;	/* WBXML Preferences */

	/* Setup list of header fields. */
	static hf_register_info hf[] = {
		{ &hf_wbxml_version,
		  { "Version",
		    "wbxml.version",
		    FT_UINT8, BASE_HEX|BASE_EXT_STRING,
		    &vals_wbxml_versions_ext, 0x00,
		    "WBXML Version", HFILL }
		},
		{ &hf_wbxml_public_id_known,
		  { "Public Identifier (known)",
		    "wbxml.public_id.known",
		    FT_UINT32, BASE_HEX|BASE_EXT_STRING,
		    &vals_wbxml_public_ids_ext, 0x00,
		    "WBXML Known Public Identifier (integer)", HFILL }
		},
		{ &hf_wbxml_public_id_literal,
		  { "Public Identifier (literal)",
		    "wbxml.public_id.literal",
		    FT_STRING, BASE_NONE,
		    NULL, 0x00,
		    "WBXML Literal Public Identifier (text string)", HFILL }
		},
		{ &hf_wbxml_charset,
		  { "Character Set",
		    "wbxml.charset",
		    FT_UINT32, BASE_HEX|BASE_EXT_STRING,
		    &wap_mib_enum_vals_character_sets_ext, 0x00,
		    "WBXML Character Set", HFILL }
		},
	};

	/* Setup protocol subtree array */
	static gint *ett[] = {
		&ett_wbxml,
		&ett_wbxml_str_tbl,
		&ett_wbxml_content,
	};

	/* Register the protocol name and description */
	proto_wbxml = proto_register_protocol(
					      "WAP Binary XML",
					      "WBXML",
					      "wbxml"
					      );

	/* Required function calls to register the header fields
	 * and subtrees used */
	proto_register_field_array(proto_wbxml, hf, array_length(hf));
	proto_register_subtree_array(ett, array_length(ett));

	/* Preferences */
	wbxml_module = prefs_register_protocol(proto_wbxml, NULL);
	prefs_register_bool_preference(wbxml_module,
				       "skip_wbxml_token_mapping",
				       "Skip the mapping of WBXML tokens to media type tokens.",
				       "Enable this preference if you want to view the WBXML "
				       "tokens without the representation in a media type "
				       "(e.g., WML). Tokens will show up as Tag_0x12, "
				       "attrStart_0x08 or attrValue_0x0B for example.",
				       &skip_wbxml_token_mapping);
	prefs_register_bool_preference(wbxml_module,
				       "disable_wbxml_token_parsing",
				       "Disable the parsing of the WBXML tokens.",
				       "Enable this preference if you want to skip the "
				       "parsing of the WBXML tokens that constitute the body "
				       "of the WBXML document. Only the WBXML header will be "
				       "dissected (and visualized) then.",
				       &disable_wbxml_token_parsing);

	register_dissector("wbxml", dissect_wbxml, proto_wbxml);
	register_dissector("wbxml-uaprof", dissect_uaprof, proto_wbxml);
}
