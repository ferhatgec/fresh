// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_point_light_object.hpp>
#include <fescript/fescript_array.hpp>
#include <fescript/modules/module_helpers.hpp>
#include <freshengine.hpp>

namespace fescript {
[[nodiscard]] Object FescriptPointLightObjectMemberGetAmbient::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.get_ambient() is not possible.\n";
    std::exit(1);
  }
  const auto& pt = this->get_self()->get_point_light();
  const auto& ambient = pt.get_ambient();
  auto arr = std::make_shared<FescriptArray>();
  arr->set_array(std::vector<Object> { static_cast<long double>(ambient.x), static_cast<long double>(ambient.y), static_cast<long double>(ambient.z) });
  return std::move(arr);
}

[[nodiscard]] Object FescriptPointLightObjectMemberGetDiffuse::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.get_diffuse() is not possible.\n";
    std::exit(1);
  }
  const auto& pt = this->get_self()->get_point_light();
  const auto& diffuse = pt.get_diffuse();
  auto arr = std::make_shared<FescriptArray>();
  arr->set_array(std::vector<Object> { static_cast<long double>(diffuse.x), static_cast<long double>(diffuse.y), static_cast<long double>(diffuse.z) });
  return std::move(arr);
}

[[nodiscard]] Object FescriptPointLightObjectMemberGetAttenuationConstant::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.get_attenuation_constant() is not possible.\n";
    std::exit(1);
  }
  return static_cast<long double>(this->get_self()->get_point_light().get_attenuation_constant());
}

[[nodiscard]] Object FescriptPointLightObjectMemberGetAttenuationLinear::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.get_attenuation_linear() is not possible.\n";
    std::exit(1);
  }
  return static_cast<long double>(this->get_self()->get_point_light().get_attenuation_linear());
}

[[nodiscard]] Object FescriptPointLightObjectMemberGetAttenuationQuadratic::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.get_attenuation_quadratic() is not possible.\n";
    std::exit(1);
  }
  return static_cast<long double>(this->get_self()->get_point_light().get_attenuation_quadratic());
}

[[nodiscard]] Object FescriptPointLightObjectMemberSetAmbient::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  ERR_CHECK_ARRAY("PointLightObject.set_ambient()", 1)
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.set_ambient() is not possible.\n";
    std::exit(1);
  }
  const auto& arr = std::get<FescriptArrayIndex>(arguments[0]);
  this->get_self()->get_point_light().set_ambient(glm::vec3 {
    std::get<LongDoubleIndex>(arr->get_value(0)),
    std::get<LongDoubleIndex>(arr->get_value(1)),
    std::get<LongDoubleIndex>(arr->get_value(2))
  });
  // TODO: [update_buffers] this might be stupid way to handle it, the better is
  // either implement a variable that works as a signal to update buffers
  // or have an init function for wrapper that takes all the parameters.
  // but since those parameters other than position does not change frequently
  // most of the time, it's okay.
  FreshInstance->get_light_manager()->update_buffers();
  return nullptr;
}

[[nodiscard]] Object FescriptPointLightObjectMemberSetDiffuse::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  ERR_CHECK_ARRAY("PointLightObject.set_diffuse()", 1)
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.set_diffuse() is not possible.\n";
    std::exit(1);
  }
  const auto& arr = std::get<FescriptArrayIndex>(arguments[0]);
  this->get_self()->get_point_light().set_diffuse(glm::vec3 {
      std::get<LongDoubleIndex>(arr->get_value(0)),
      std::get<LongDoubleIndex>(arr->get_value(1)),
      std::get<LongDoubleIndex>(arr->get_value(2))
  });
  // TODO: see [update_buffers]
  FreshInstance->get_light_manager()->update_buffers();
  return nullptr;
}

[[nodiscard]] Object FescriptPointLightObjectMemberSetAttenuationConstant::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  ERR_CHECK_DECIMAL("PointLightObject.set_attenuation_constant()", 1)
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.set_attenuation_constant() is not possible.\n";
    std::exit(1);
  }
  auto att = std::get<LongDoubleIndex>(arguments[0]);
  this->get_self()->get_point_light().set_attenuation_constant(static_cast<idk::f32>(att));
  // TODO: see [update_buffers]
  FreshInstance->get_light_manager()->update_buffers();
  return nullptr;
}

[[nodiscard]] Object FescriptPointLightObjectMemberSetAttenuationLinear::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  ERR_CHECK_DECIMAL("PointLightObject.set_attenuation_linear()", 1)
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.set_attenuation_linear() is not possible.\n";
    std::exit(1);
  }
  auto att = std::get<LongDoubleIndex>(arguments[0]);
  this->get_self()->get_point_light().set_attenuation_linear(static_cast<idk::f32>(att));
  // TODO: see [update_buffers]
  FreshInstance->get_light_manager()->update_buffers();
  return nullptr;
}

[[nodiscard]] Object FescriptPointLightObjectMemberSetAttenuationQuadratic::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  ERR_CHECK_DECIMAL("PointLightObject.set_attenuation_quadratic()", 1)
  if(!this->_self) {
    std::cout << "Engine error: PointLightObject is not initialized, yet using PointLightObject.set_attenuation_quadratic() is not possible.\n";
    std::exit(1);
  }
  auto att = std::get<LongDoubleIndex>(arguments[0]);
  this->get_self()->get_point_light().set_attenuation_quadratic(static_cast<idk::f32>(att));
  // TODO: see [update_buffers]
  FreshInstance->get_light_manager()->update_buffers();
  return nullptr;
}

[[nodiscard]] Object FescriptPointLightObjectWrapper::call(
    [[maybe_unused]] Interpreter& interpreter,
    const std::vector<Object>& arguments
) {
  // pos, ambient, diffuse, constant, linear, quadratic
  if(arguments.size() == 6) {
    const auto& pos = std::get<FescriptArrayIndex>(arguments[0]);
    const auto& ambient = std::get<FescriptArrayIndex>(arguments[1]);
    const auto& diffuse = std::get<FescriptArrayIndex>(arguments[2]);
    const auto constant = std::get<LongDoubleIndex>(arguments[3]);
    const auto linear = std::get<LongDoubleIndex>(arguments[4]);
    const auto quadratic = std::get<LongDoubleIndex>(arguments[5]);
    auto pt_object = std::make_shared<fresh::PointLightObject>(
        // pos
        fresh::PointResource(
          static_cast<idk::f32>(std::get<LongDoubleIndex>(pos->get_value(0))),
          static_cast<idk::f32>(std::get<LongDoubleIndex>(pos->get_value(1)))
        ),
        // ambient
        glm::vec3(
          static_cast<idk::f32>(std::get<LongDoubleIndex>(ambient->get_value(0))),
          static_cast<idk::f32>(std::get<LongDoubleIndex>(ambient->get_value(1))),
          static_cast<idk::f32>(std::get<LongDoubleIndex>(ambient->get_value(2)))
        ),
        // diffuse
        glm::vec3(
          static_cast<idk::f32>(std::get<LongDoubleIndex>(diffuse->get_value(0))),
          static_cast<idk::f32>(std::get<LongDoubleIndex>(diffuse->get_value(1))),
          static_cast<idk::f32>(std::get<LongDoubleIndex>(diffuse->get_value(2)))
        ),
        constant,
        linear,
        quadratic
    );
    this->_object_id = pt_object->get_id();
    return std::move(pt_object);
  }
  auto pt_object = std::make_shared<fresh::PointLightObject>();
  this->_object_id = pt_object->get_id();
  return std::move(pt_object);
}
} // namespace fescript