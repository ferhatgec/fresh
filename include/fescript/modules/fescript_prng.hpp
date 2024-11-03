// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "module_helpers.hpp"
#include <fescript/fescript_callable.hpp>
#include <fescript/fescript_class.hpp>
#include <types/predefined.hpp>

#define PRNG_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, PRNG, arg_count)
#define PRNG_GLOBAL_CONSTANT(name, value) this->globals->define(name, static_cast<idk::f80>(value));

enum FescriptPRNG : std::uint8_t {
  LehmerPRNGIndex,
  LinearCongruentialPRNGIndex,
  MersenneTwisterPRNGIndex,
  MultiplyWithCarryIndex,
  XorshiftPRNGIndex,
  GechPRNGIndex
};

#define PRNG_GLOBAL_CONSTANTS() \
  PRNG_GLOBAL_CONSTANT("PRNG_Lehmer", LehmerPRNGIndex) \
  PRNG_GLOBAL_CONSTANT("PRNG_LinearCongruential", LinearCongruentialPRNGIndex) \
  PRNG_GLOBAL_CONSTANT("PRNG_MersenneTwister", MersenneTwisterPRNGIndex) \
  PRNG_GLOBAL_CONSTANT("PRNG_MultiplyWithCarry", MultiplyWithCarryIndex) \
  PRNG_GLOBAL_CONSTANT("PRNG_Xorshift", XorshiftPRNGIndex) \
  PRNG_GLOBAL_CONSTANT("PRNG_Gech", GechPRNGIndex)

namespace fescript {
PRNG_MODULE(GetGlobalSeed, 0)
PRNG_MODULE(SetGlobalSeed, 1)
PRNG_MODULE(GeneratePRN, 1)
PRNG_MODULE(GeneratePRNBetween, 3)
} // namespace fescript

#undef PRNG_MODULE