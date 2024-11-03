// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "module_helpers.hpp"
#include <fescript/fescript_class.hpp>
#include <fescript/fescript_callable.hpp>
#include <types/predefined.hpp>

#define MATH_GLOBAL_CONSTANT(name, value) this->globals->define(name, static_cast<idk::f80>(value));
#define MATH_GLOBAL_FUNCTION(name, def_type) this->globals->define(name, std::make_shared<##def_type>());
#define MATH_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, Math, arg_count)
#define MATH_GLOBAL_CONSTANTS() \
  MATH_GLOBAL_CONSTANT("Math_Pi", __idk_pi) \
  MATH_GLOBAL_CONSTANT("Math_E", __idk_e)   \
  MATH_GLOBAL_CONSTANT("Math_Phi", __idk_phi) \
  MATH_GLOBAL_CONSTANT("Math_Tau", __idk_tau)

#define MATH_GLOBAL_FUNCTIONS() \
  MATH_GLOBAL_FUNCTION("Math_abs", FescriptMathAbs) \
  MATH_GLOBAL_FUNCTION("Math_max", FescriptMathMax) \
  MATH_GLOBAL_FUNCTION("Math_min", FescriptMathMin) \
  MATH_GLOBAL_FUNCTION("Math_exp", FescriptMathExp) \
  MATH_GLOBAL_FUNCTION("Math_log", FescriptMathLog) \
  MATH_GLOBAL_FUNCTION("Math_pow", FescriptMathPow) \
  MATH_GLOBAL_FUNCTION("Math_sqrt", FescriptMathSqrt) \
  MATH_GLOBAL_FUNCTION("Math_cbrt", FescriptMathCbrt) \
  MATH_GLOBAL_FUNCTION("Math_sin", FescriptMathSin) \
  MATH_GLOBAL_FUNCTION("Math_cos", FescriptMathCos) \
  MATH_GLOBAL_FUNCTION("Math_tan", FescriptMathTan) \
  MATH_GLOBAL_FUNCTION("Math_asin", FescriptMathAsin) \
  MATH_GLOBAL_FUNCTION("Math_acos", FescriptMathAcos) \
  MATH_GLOBAL_FUNCTION("Math_atan", FescriptMathAtan) \
  MATH_GLOBAL_FUNCTION("Math_sinh", FescriptMathSinh) \
  MATH_GLOBAL_FUNCTION("Math_cosh", FescriptMathCosh) \
  MATH_GLOBAL_FUNCTION("Math_tanh", FescriptMathTanh) \
  MATH_GLOBAL_FUNCTION("Math_asinh", FescriptMathAsinh) \
  MATH_GLOBAL_FUNCTION("Math_acosh", FescriptMathAcosh) \
  MATH_GLOBAL_FUNCTION("Math_atanh", FescriptMathAtanh) \
  MATH_GLOBAL_FUNCTION("Math_erf", FescriptMathErf) \
  MATH_GLOBAL_FUNCTION("Math_gamma", FescriptMathGamma) \
  MATH_GLOBAL_FUNCTION("Math_ceil", FescriptMathCeil) \
  MATH_GLOBAL_FUNCTION("Math_floor", FescriptMathFloor) \
  MATH_GLOBAL_FUNCTION("Math_trunc", FescriptMathTrunc) \
  MATH_GLOBAL_FUNCTION("Math_round", FescriptMathRound) \
  MATH_GLOBAL_FUNCTION("Math_sgn", FescriptMathSgn) \
  MATH_GLOBAL_FUNCTION("Math_degs_to_rads", FescriptMathDegreesToRadians) \
  MATH_GLOBAL_FUNCTION("Math_rads_to_degs", FescriptMathRadiansToDegrees)

namespace fescript {
static inline constexpr idk::f80 pi_180 = __idk_pi / 180.0;
static inline constexpr idk::f80 _180_pi = 180.0 / __idk_pi;

MATH_MODULE(Abs, 1)
MATH_MODULE(Max, -1)
MATH_MODULE(Min, -1)
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
MATH_MODULE(Sgn, 1)
MATH_MODULE(DegreesToRadians, 1)
MATH_MODULE(RadiansToDegrees, 1)
} // namespace fescript

#undef MATH_MODULE