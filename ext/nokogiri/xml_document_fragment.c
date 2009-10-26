#include <xml_document_fragment.h>

/*
 * call-seq:
 *  new(document)
 *
 * Create a new DocumentFragment element on the +document+
 */
static VALUE new(VALUE klass, SEL sel, int argc, VALUE *argv)
{
  xmlDocPtr xml_doc;
  VALUE document;
  VALUE rest;

  rb_scan_args(argc, argv, "1*", &document, &rest);

  Data_Get_Struct(document, xmlDoc, xml_doc);

  xmlNodePtr node = xmlNewDocFragment(xml_doc->doc);
  if(node->doc->children)
    node->ns = node->doc->children->ns;

  NOKOGIRI_ROOT_NODE(node);

  VALUE rb_node = Nokogiri_wrap_xml_node(klass, node);
  rb_obj_call_init(rb_node, argc, argv);

  if(rb_block_given_p()) rb_yield(rb_node);

  return rb_node;
}

VALUE cNokogiriXmlDocumentFragment;
void init_xml_document_fragment()
{
  VALUE nokogiri = rb_define_module("Nokogiri");
  VALUE xml = rb_define_module_under(nokogiri, "XML");
  VALUE node = rb_define_class_under(xml, "Node", rb_cObject);

  /*
   * DocumentFragment represents a DocumentFragment node in an xml document.
   */
  VALUE klass = rb_define_class_under(xml, "DocumentFragment", node);

  cNokogiriXmlDocumentFragment = klass;

  rb_objc_define_method(*(VALUE *)klass, "new", new, -1);
}
