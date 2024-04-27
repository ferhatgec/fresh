#pragma once

#include "module_helpers.hpp"
#include "../fescript_class.hpp"
#include "../fescript_callable.hpp"
#include "../../../libs/idk/idk/types/predefined.hpp"

#define MATH_GLOBAL_CONSTANT(name, value) this->globals->define(name, static_cast<idk::f80>(value));
#define MATH_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, Math, arg_count)

#define MATH_GLOBAL_CONSTANTS() \
MATH_GLOBAL_CONSTANT("Math_Pi", __idk_pi) \
MATH_GLOBAL_CONSTANT("Math_E", __idk_e)   \
MATH_GLOBAL_CONSTANT("Math_Phi", __idk_phi) \
MATH_GLOBAL_CONSTANT("Math_Tau", __idk_tau)

namespace fescript {
MATH_MODULE(Abs, 1)
MATH_MODULE(Max, 2)
MATH_MODULE(Min, 2)
MATH_MODULE(Exp, 1)
MATH_MODULE(Log, 2)
MATH_MODULE(Pow, 2)
MATH_MODULE(Sqrt, 1)
MATH_MODULE(Cbrt, 1)
MATH_MODULE(Sin, 1)
MATH_MODULE(Cos, 1)
MATH_MODULE(Tan, 1)
MATH_MODULE(Asin, 1)
MATH_MODULE(Acos, 1)
MATH_MODULE(Atan, 1)
MATH_MODULE(Sinh, 1)
MATH_MODULE(Cosh, 1)
MATH_MODULE(Tanh, 1)
MATH_MODULE(Asinh, 1)
MATH_MODULE(Acosh, 1)
MATH_MODULE(Atanh, 1)
MATH_MODULE(Erf, 1)
MATH_MODULE(Gamma, 1)
MATH_MODULE(Ceil, 1)
MATH_MODULE(Floor, 1)
MATH_MODULE(Trunc, 1)
MATH_MODULE(Round, 1)
}

#undef MATH_MODULE