// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/modules/fescript_prng.hpp>
#include <fescript/fescript_array.hpp>
#include <random/random.hpp>
#include <freshengine.hpp>
#include <limits>

#undef max
#undef min

namespace fescript {
// output: decimal
[[nodiscard]] Object FescriptPRNGGetGlobalSeed::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return static_cast<idk::f80>(interpreter.get_global_seed());
}

// output: decimal
[[nodiscard]] Object FescriptPRNGSetGlobalSeed::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("PRNG_set_global_seed", 1)
  interpreter.get_global_seed() = static_cast<idk::i64>(std::get<LongDoubleIndex>(arguments.front()));
  return static_cast<idk::f80>(interpreter.get_global_seed());
}

// output: decimal, limited between [0, 2^32 - 2]
[[nodiscard]] Object FescriptPRNGGeneratePRN::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("PRNG_generate_prn", 1)
  interpreter.get_global_seed() = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
    ).count();
  switch(static_cast<idk::i64>(std::get<LongDoubleIndex>(arguments.front()))) {
    case LehmerPRNGIndex: {
      idk::LehmerGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>::max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case LinearCongruentialPRNGIndex: {
      idk::LinearCongruentialGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>::max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case MultiplyWithCarryIndex: {
      idk::MultiplyWithCarryGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>::max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case XorshiftPRNGIndex: {
      idk::XorshiftGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>::max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case GechPRNGIndex: {
      idk::GechGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>::max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
    case MersenneTwisterPRNGIndex: {
      [[fallthrough]];
    }
    default: {
      idk::MersenneTwisterGenerator gen(interpreter.get_global_seed());
      gen._btw_end_pos = std::numeric_limits<idk::i32>::max() - 2;
      gen._btw_start_pos = 0;
      return static_cast<idk::f80>(gen.take());
    }
  }
}

// output: decimal, between [0, 2^32 - 2]
[[nodiscard]] Object FescriptPRNGGeneratePRNBetween::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("PRNG_generate_prn_between", 3)
  interpreter.get_global_seed() = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
    ).count();
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