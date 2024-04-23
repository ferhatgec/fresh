#pragma once

#include "module_helpers.hpp"
#include "../fescript_class.hpp"
#include "../fescript_callable.hpp"
#include "../../../libs/idk/idk/types/predefined.hpp"

#define PATH_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, Path, arg_count)

namespace fescript {
PATH_MODULE(Exists, 1)
PATH_MODULE(IsDir, 1)
PATH_MODULE(IsFile, 1)
PATH_MODULE(IsSymlink, 1)
PATH_MODULE(IsSocket, 1)
PATH_MODULE(IsEmpty, 1)
PATH_MODULE(Cwd, 0)
PATH_MODULE(Rwalk, 1)
PATH_MODULE(Walk, 1)
PATH_MODULE(ReadFile, 1)
PATH_MODULE(WriteFile, 2)
}

#undef PATH_MODULE