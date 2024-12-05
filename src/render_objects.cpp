// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <render_objects.hpp>
#include <freshengine.hpp>
#include <log/log.hpp>

namespace fresh {
/// RenderObjects::get_object searches rendered base object list linearly.
/// if it finds; then const reference of shared_ptr will be returned.
[[nodiscard]] const std::shared_ptr<BaseObject>& RenderObjects::get_object(std::string_view object_name) noexcept {
  for(const auto& sptr: RenderObjects::objects_to_render) {
    if(sptr && sptr->get_name() == object_name) {
      return sptr;
    }
  }
  log_error(fresh::src(), "RenderObjects::get_object({}) cannot be found.", object_name);
  return RenderObjects::NullptrRefer;
}

/// RenderObjects::get_object(std::size_t) searches rendered base object list linearly by
/// object_id.
[[nodiscard]] const std::shared_ptr<BaseObject>& RenderObjects::get_object(std::size_t object_id) noexcept {
  for(const auto& sptr: RenderObjects::objects_to_render) {
    if(sptr && sptr->get_id() == object_id) {
      return sptr;
    }
  }
  log_error(fresh::src(), "RenderObjects::get_object({}) cannot be found.", object_id);
  return RenderObjects::NullptrRefer;
}

/// RenderObjects::get_index_of_object returns index of given object.
/// if object won't be found; then RenderObjects::NotFound will be returned.
[[nodiscard]] std::size_t RenderObjects::get_index_of_object(std::string_view object_name) noexcept {
  for(std::size_t i = 0; i < RenderObjects::objects_to_render.size(); ++i) {
    const auto& sptr = RenderObjects::objects_to_render[i];
    if(sptr && sptr->get_name().data() == object_name) {
      return i;
    }
  }
  return RenderObjects::NotFound;
}

/// RenderObjects::push_object shares the ownership of given object and
/// pushes back of rendered base objects list.
void RenderObjects::push_object(std::shared_ptr<BaseObject> object) noexcept {
  if(!object) {
    log_error(fresh::src(), "RenderObjects::push_object() cannot push since object is empty or nullptr.");
    return;
  }
  RenderObjects::objects_to_render.push_back(std::move(object));
}

/// RenderObjects::pop_object removes given object from rendered base objects list,
/// then gives you the shared pointer. if you don't want to get the shared pointer or
/// want to delete it later; then use RenderObjects::pop_object_delete, which will delete it in-place.
[[nodiscard]] std::shared_ptr<BaseObject>&& RenderObjects::pop_object(std::string_view object_name) noexcept {
  auto sptr_index = RenderObjects::get_index_of_object(object_name);
  if(sptr_index == RenderObjects::NotFound) {
    log_error(fresh::src(), "RenderObjects::pop_object() cannot pop since object is empty or nullptr.");
    return nullptr;
  }
  auto sptr = std::move(RenderObjects::objects_to_render[sptr_index]); // now RenderObjects::objects_to_render is empty.
  RenderObjects::objects_to_render.erase(RenderObjects::objects_to_render.begin() + static_cast<std::make_signed_t<decltype(sptr_index)>>(sptr_index));
  return std::move(sptr);
}

/// RenderObjects::pop_object_delete removes given object from rendered base objects list,
/// but will not give you the ownership of pointer. syntactic sugar for RenderObjects::pop_object() then unique_ptr::reset().
void RenderObjects::pop_object_delete(std::string_view object_name) noexcept {
  auto sptr = std::move(RenderObjects::pop_object(object_name));
  if(!sptr) {
    log_error(fresh::src(), "RenderObjects::pop_object_delete() cannot pop since object is empty or nullptr.");
    return;
  }
  sptr.reset();
}
} // namespace fresh