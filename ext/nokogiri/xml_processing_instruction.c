#include <xml_processing_instruction.h>

/*
 * call-seq:
 *  new(document, name, content)
 *
 * Create a new ProcessingInstruction element on the +document+ with +name+
 * and +content+
 */
static VALUE new(VALUE klass, SEL sel, int argc, VALUE *argv)
{
  xmlDocPtr xml_doc;
  VALUE document;
  VALUE name;
  VALUE content;
  VALUE rest;

  rb_scan_args(argc, argv, "3*", &document, &name, &content, &rest);

  Data_Get_Struct(document, xmlDoc, xml_doc);

  xmlNodePtr node = xmlNewDocPI(
      xml_doc,
      (const xmlChar *)StringValuePtr(name),
      (const xmlChar *)StringValuePtr(content)
  );

  NOKOGIRI_ROOT_NODE(node);

  VALUE rb_node = Nokogiri_wrap_xml_node(klass, node);
  rb_obj_call_init(rb_node, argc, argv);

  if(rb_block_given_p()) rb_yield(rb_node);

  return rb_node;
}

VALUE cNokogiriXmlProcessingInstruction;
void init_xml_processing_instruction()
{
  VALUE nokogiri = rb_define_module("Nokogiri");
  VALUE xml = rb_define_module_under(nokogiri, "XML");
  VALUE node = rb_define_class_under(xml, "Node", rb_cObject);

  /*
   * ProcessingInstruction represents a ProcessingInstruction node in an xml
   * document.
   */
  VALUE klass = rb_define_class_under(xml, "ProcessingInstruction", node);

  cNokogiriXmlProcessingInstruction = klass;

  rb_objc_define_method(*(VALUE *)klass, "new", new, -1);
}
