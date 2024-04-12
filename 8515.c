PHP_FUNCTION(dom_document_save_html)
{
	zval *id, *nodep = NULL;
	xmlDoc *docp;
	xmlNode *node;
	xmlBufferPtr buf;
	dom_object *intern, *nodeobj;
	xmlChar *mem = NULL;
	int size = 0, format;
	dom_doc_propsptr doc_props;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(),
		"O|O!", &id, dom_document_class_entry, &nodep, dom_node_class_entry)
		== FAILURE) {
		return;
	}

	DOM_GET_OBJ(docp, id, xmlDocPtr, intern);

	doc_props = dom_get_doc_props(intern->document);
	format = doc_props->formatoutput;

	if (nodep != NULL) {
		/* Dump contents of Node */
		DOM_GET_OBJ(node, nodep, xmlNodePtr, nodeobj);
		if (node->doc != docp) {
			php_dom_throw_error(WRONG_DOCUMENT_ERR, dom_get_strict_error(intern->document) TSRMLS_CC);
			RETURN_FALSE;
		}
		
		buf = xmlBufferCreate();
		if (!buf) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Could not fetch buffer");
			RETURN_FALSE;
		}
		
		if (node->type == XML_DOCUMENT_FRAG_NODE) {
			int one_size;

			for (node = node->children; node; node = node->next) {
				one_size = htmlNodeDump(buf, docp, node);

				if (one_size >= 0) {
					size += one_size;
				} else {
					size = -1;
					break;
				}
			}
		} else {
			size = htmlNodeDump(buf, docp, node);
		}
		if (size >= 0) {
			mem = (xmlChar*) xmlBufferContent(buf);
			if (!mem) {
				RETVAL_FALSE;
			} else {
				RETVAL_STRINGL((const char*) mem, size, 1);
			}
		} else {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Error dumping HTML node");
			RETVAL_FALSE;
		}
		xmlBufferFree(buf);
	} else {
#if LIBXML_VERSION >= 20623
		htmlDocDumpMemoryFormat(docp, &mem, &size, format);
#else
		htmlDocDumpMemory(docp, &mem, &size);
#endif
		if (!size) {
			RETVAL_FALSE;
		} else {
			RETVAL_STRINGL((const char*) mem, size, 1);
		}
		if (mem)
			xmlFree(mem);
	}

}
