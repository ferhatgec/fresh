#include "include/fes/fes_parser.hpp"
#include <iostream>

int main() {
  fresh::fes::FesParser parser;
  parser.get_tokenizer().load_from("freshengine_scene.fes", true);
  parser.get_tokenizer().tokenize();
  parser.parse();

  for(auto& node: parser._objects->_sub_groups) {
    std::cout << node->_width << " " << node->_height << " " <<
                  node->_sub_groups.back()->_width << " " << node->_sub_groups.back()->_height << '\n';
  }
}