// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/modules/fescript_math.hpp>
#include <iostream>

namespace fescript {
[[nodiscard]] Object FescriptMathAbs::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_abs()", 1)
  return fabsl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathMax::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  idk::f80 current_maximum = std::numeric_limits<idk::f80>().min();
  for(const auto& arg: arguments) {
    if(arg.index() != LongDoubleIndex) {
      std::cout << "Engine [language] error: Math_max() must take decimal.\n";
      std::exit(1);
    }
    current_maximum = fmaxl(current_maximum, std::get<LongDoubleIndex>(arg));
  }
  return current_maximum; // returns minimum value of long double if no argument given
}

[[nodiscard]] Object FescriptMathMin::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  idk::f80 current_minimum = std::numeric_limits<idk::f80>().max();
  for(const auto& arg: arguments) {
    if(arg.index() != LongDoubleIndex) {
      std::cout << "Engine [language] error: Math_min() must take decimal.\n";
      std::exit(1);
    }
    current_minimum = fminl(current_minimum, std::get<LongDoubleIndex>(arg));
  }
  return current_minimum; // returns maximum value of long double if no argument given
}

[[nodiscard]] Object FescriptMathExp::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_exp()", 1)
  return expl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathLog::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_log()", 2)
  return logl(std::get<LongDoubleIndex>(arguments[0])) / logl(std::get<LongDoubleIndex>(arguments[1]));
}

[[nodiscard]] Object FescriptMathPow::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_pow()", 2)
  return powl(std::get<LongDoubleIndex>(arguments[0]), std::get<LongDoubleIndex>(arguments[1]));
}

[[nodiscard]] Object FescriptMathSqrt::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_sqrt()", 1)
  return sqrtl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathCbrt::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_cbrt()", 1)
  return cbrtl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathSin::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_sin()", 1)
  return sinl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathCos::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_cos()", 1)
  return cosl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathTan::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_tan()", 1)
  return tanl(std::get<LongDoubleIndex>(arguments.front()));
}
[[nodiscard]] Object FescriptMathAsin::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_asin()", 1)
  return asinl(std::get<LongDoubleIndex>(arguments.front()));
}
[[nodiscard]] Object FescriptMathAcos::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_acos()", 1)
  return acosl(std::get<LongDoubleIndex>(arguments.front()));
}
[[nodiscard]] Object FescriptMathAtan::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_atan()", 1)
  return atanl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathSinh::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_sinh()", 1)
  return sinhl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathCosh::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_cosh()", 1)
  return coshl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathTanh::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_tanh()", 1)
  return tanhl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathAsinh::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_asinh()", 1)
  return asinhl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathAcosh::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_acosh()", 1)
  return acoshl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathAtanh::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_atanh()", 1)
  return atanhl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathErf::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_erf()", 1)
  return erfl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathGamma::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_gamma()", 1)
  return tgammal(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathCeil::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_ceil()", 1)
  return ceill(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathFloor::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_floor()", 1)
  return floorl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathTrunc::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_trunc()", 1)
  return truncl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathRound::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_round()", 1)
  return roundl(std::get<LongDoubleIndex>(arguments.front()));
}

[[nodiscard]] Object FescriptMathSgn::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_sgn()", 1)
  const auto& dec = std::get<LongDoubleIndex>(arguments.front());
  if(dec > 0)
    return 1_f80;
  if(dec < 0)
    return -1_f80;
  return 0_f80;
}

[[nodiscard]] Object FescriptMathDegreesToRadians::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_degs_to_rads", 1)
  return std::get<LongDoubleIndex>(arguments.front()) * pi_180;
}

[[nodiscard]] Object FescriptMathRadiansToDegrees::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("Math_rads_to_degs", 1)
  return std::get<LongDoubleIndex>(arguments.front()) * _180_pi;
}
}