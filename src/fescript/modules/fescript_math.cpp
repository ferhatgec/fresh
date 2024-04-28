#include <iostream>
#include "../../../include/fescript/modules/fescript_math.hpp"

namespace fescript {
__idk_nodiscard Object FescriptMathAbs::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_abs()", 1)
  return fabsl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathMax::call(Interpreter &interpreter, std::vector<Object> arguments) {
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

__idk_nodiscard Object FescriptMathMin::call(Interpreter &interpreter, std::vector<Object> arguments) {
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

__idk_nodiscard Object FescriptMathExp::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_exp()", 1)
  return expl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathLog::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_log()", 2)
  return logl(std::get<LongDoubleIndex>(arguments[0])) / logl(std::get<LongDoubleIndex>(arguments[1]));
}

__idk_nodiscard Object FescriptMathPow::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_pow()", 2)
  return powl(std::get<LongDoubleIndex>(arguments[0]), std::get<LongDoubleIndex>(arguments[1]));
}

__idk_nodiscard Object FescriptMathSqrt::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_sqrt()", 1)
  return sqrtl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathCbrt::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_cbrt()", 1)
  return cbrtl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathSin::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_sin()", 1)
  return sinl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathCos::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_cos()", 1)
  return cosl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathTan::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_tan()", 1)
  return tanl(std::get<LongDoubleIndex>(arguments.front()));
}
__idk_nodiscard Object FescriptMathAsin::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_asin()", 1)
  return asinl(std::get<LongDoubleIndex>(arguments.front()));
}
__idk_nodiscard Object FescriptMathAcos::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_acos()", 1)
  return acosl(std::get<LongDoubleIndex>(arguments.front()));
}
__idk_nodiscard Object FescriptMathAtan::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_atan()", 1)
  return atanl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathSinh::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_sinh()", 1)
  return sinhl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathCosh::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_cosh()", 1)
  return coshl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathTanh::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_tanh()", 1)
  return tanhl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathAsinh::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_asinh()", 1)
  return asinhl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathAcosh::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_acosh()", 1)
  return acoshl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathAtanh::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_atanh()", 1)
  return atanhl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathErf::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_erf()", 1)
  return erfl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathGamma::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_gamma()", 1)
  return tgammal(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathCeil::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_ceil()", 1)
  return ceill(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathFloor::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_floor()", 1)
  return floorl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathTrunc::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_trunc()", 1)
  return truncl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathRound::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("Math_round()", 1)
  return roundl(std::get<LongDoubleIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptMathSgn::call(fescript::Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("Math_sgn()", 1)
  const auto& dec = std::get<LongDoubleIndex>(arguments.front());
  if(dec > 0)
    return 1_f80;
  if(dec < 0)
    return -1_f80;
  return 0_f80;
}

__idk_nodiscard Object FescriptMathDegreesToRadians::call(fescript::Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("Math_degs_to_rads", 1)
  return std::get<LongDoubleIndex>(arguments.front()) * pi_180;
}

__idk_nodiscard Object FescriptMathRadiansToDegrees::call(fescript::Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("Math_rads_to_degs", 1)
  return std::get<LongDoubleIndex>(arguments.front()) * _180_pi;
}
}