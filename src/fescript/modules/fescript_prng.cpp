#include "../../../include/fescript/modules/fescript_prng.hpp"
#include "../../../include/fescript/fescript_array.hpp"
#include "../../../include/freshengine.hpp"
#include "../../../libs/idk/idk/random/random.hpp"
#include <limits>

namespace fescript {
// output: decimal
__idk_nodiscard Object FescriptPRNGGetGlobalSeed::call(Interpreter& interpreter, std::vector <Object> arguments) {
  return static_cast<idk::f80>(interpreter.get_global_seed());
}

// output: decimal
__idk_nodiscard Object FescriptPRNGSetGlobalSeed::call(fescript::Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("PRNG_set_global_seed", 1)
  interpreter.get_global_seed() = static_cast<idk::i64>(std::get<LongDoubleIndex>(arguments.front()));
  return static_cast<idk::f80>(interpreter.get_global_seed());
}

// output: decimal, limited between [0, 2^32 - 2]
__idk_nodiscard Object FescriptPRNGGeneratePRN::call(fescript::Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("PRNG_generate_prn", 1)
  switch(static_cast<idk::i64>(std::get<LongDoubleIndex>(arguments.front()))) {
    case LehmerPRNGIndex: {
      idk::LehmerGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>().max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case LinearCongruentialPRNGIndex: {
      idk::LinearCongruentialGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>().max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case MultiplyWithCarryIndex: {
      idk::MultiplyWithCarryGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>().max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case XorshiftPRNGIndex: {
      idk::XorshiftGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>().max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case GechPRNGIndex: {
      idk::GechGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>().max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case MersenneTwisterPRNGIndex: {
      [[fallthrough]];
    }
    default: {
      idk::MersenneTwisterGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>().max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
  }
}

// output: decimal, between [0, 2^32 - 2]
__idk_nodiscard Object FescriptPRNGGeneratePRNBetween::call(fescript::Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("PRNG_generate_prn_between", 3)
  switch(static_cast<idk::i64>(std::get<LongDoubleIndex>(arguments.front()))) {
    case LehmerPRNGIndex: {
      idk::LehmerGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[2]));
      gen._btw_start_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[1]));
      return static_cast<idk::f80>(gen.take());
    }
    case LinearCongruentialPRNGIndex: {
      idk::LinearCongruentialGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[2]));
      gen._btw_start_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[1]));
      return static_cast<idk::f80>(gen.take());
    }
    case MultiplyWithCarryIndex: {
      idk::MultiplyWithCarryGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[2]));
      gen._btw_start_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[1]));
      return static_cast<idk::f80>(gen.take());
    }
    case XorshiftPRNGIndex: {
      idk::XorshiftGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[2]));
      gen._btw_start_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[1]));
      return static_cast<idk::f80>(gen.take());
    }
    case GechPRNGIndex: {
      idk::GechGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[2]));
      gen._btw_start_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[1]));
      return static_cast<idk::f80>(gen.take());
    }
    case MersenneTwisterPRNGIndex: {
      [[fallthrough]];
    }
    default: {
      idk::MersenneTwisterGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[2]));
      gen._btw_start_pos = static_cast<idk::u32>(std::get<LongDoubleIndex>(arguments[1]));
      return static_cast<idk::f80>(gen.take());
    }
  }
}
} // namespace fescript