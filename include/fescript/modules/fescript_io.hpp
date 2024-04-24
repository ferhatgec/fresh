#pragma once

#include "module_helpers.hpp"
#include "../fescript_class.hpp"
#include "../fescript_callable.hpp"
#include "../../../libs/idk/idk/types/predefined.hpp"

#define IO_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, IO, arg_count)

namespace fescript {
IO_MODULE(Print, -1)
IO_MODULE(Println, -1)
IO_MODULE(ReadFile, 1)
IO_MODULE(WriteFile, 2)
IO_MODULE(Input, -1)
IO_MODULE(CharInput, -1)
}

#undef PATH_MODULE