#pragma once

#include "module_helpers.hpp"
#include <fescript/fescript_class.hpp>
#include <fescript/fescript_callable.hpp>
#include <types/predefined.hpp>
#include <functional>

#define PATH_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, Path, arg_count)

namespace fescript {
PATH_MODULE(Exists, -1)
PATH_MODULE(IsDir, -1)
PATH_MODULE(IsFile, -1)
PATH_MODULE(IsSymlink, -1)
PATH_MODULE(IsSocket, -1)
PATH_MODULE(IsEmpty, -1)
PATH_MODULE(Cwd, 0)
PATH_MODULE(Rwalk, 1)
PATH_MODULE(Walk, 1)
} // namespace fescript

#undef PATH_MODULE