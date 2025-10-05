// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <filesystem>
#include <freshengine.hpp>
#include <resources/fes_loader_resource.hpp>
#include <string>

#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/polygon_area_object.hpp>
#include <objects/circle_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/polygon_object.hpp>
#include <objects/rectangle_object.hpp>
#include <objects/point_light_object.hpp>

namespace fresh {
[[nodiscard]] fes::FesParser& FesLoaderResource::get_parser() noexcept {
  return this->_parser;
}

void FesLoaderResource::load_fes(const std::string& ctx,
                                 bool is_file) noexcept {
  this->_file = is_file;
  this->_ctx = ctx;
  this->get_parser().get_tokenizer().load_from(ctx, is_file);
  this->get_parser().get_tokenizer().tokenize();
  this->get_parser().parse();
}

[[nodiscard]] std::shared_ptr<BaseObject> FesLoaderResource::generate() noexcept {
  return std::move(generate_from_ast(this->get_parser()._objects));
}

[[nodiscard]] std::shared_ptr<BaseObject> FesLoaderResource::generate_from_ast(
    const std::shared_ptr<fes::FesObjectAST>& fes_obj
) noexcept {
  const auto& fes_obj_type = fes_obj->get_type();
  auto gen_obj = std::move(FesLoaderResource::_create_object(fes_obj_type));
  // FesLoaderResource::_create_object(Keywords) returns nullptr if given type
  // is not BaseObject or -derived type. only one exception here is fes::Import;
  // since it does not store anything like in FesImportObjectAST or something;
  // it just loads given file.
  if (!gen_obj && fes_obj_type == fes::Import) {
    const auto& import_obj =
        std::static_pointer_cast<fes::FesImportObjectAST>(fes_obj);
    FesLoaderResource res;
    res.load_fes(import_obj->get_import_path());
    gen_obj = res.generate();
    if (!gen_obj) {
      log_error(src(), "import: generated object is invalid: '{}'",
                import_obj->get_import_path());
      return nullptr;
    }
    gen_obj->imported_from = import_obj->get_import_path();
    return std::move(gen_obj);
  }
  if (!gen_obj) {
    log_error(src(),
              "generated object is invalid."
              "this might be bug since type directly passed using "
              "fes_obj->get_type(). '{}'",
              fes_obj->get_name());
    return nullptr;
  }

  _set_baseobject_properties(fes_obj, gen_obj);
  // now we fill object specific properties; we filled BaseObject and Import;
  // so they are excluded; types with no exclusive properties are excluded here.
  switch (fes_obj_type) {
    case fes::LabelObject: {
      const auto& fes_label_obj =
          std::static_pointer_cast<fes::FesLabelObjectAST>(fes_obj);
      const auto& label_obj =
          std::static_pointer_cast<fresh::LabelObject>(gen_obj);
      fresh::FontResource font_res;

      if(fes_label_obj->get_label_path().empty()) {
        log_error(src(), "label path is empty.");
        return nullptr;
      }
      font_res.set_font_size(fes_label_obj->get_font_size());
      font_res.load_font(fes_label_obj->get_label_path());
      label_obj->get_label_font_resource() = font_res;
      label_obj->set_position({
        fes_label_obj->get_position().get_x(),
        fes_label_obj->get_position().get_y(),
        fes_label_obj->get_size().get_w(),
        fes_label_obj->get_size().get_h()
      });
      label_obj->set_label_text(fes_label_obj->get_label_text());
      break;
    }
    case fes::SpriteObject: {
      const auto& fes_sprite_obj = std::static_pointer_cast<fes::FesSpriteObjectAST>(fes_obj);
      const auto& sprite_obj = std::static_pointer_cast<fresh::SpriteObject>(gen_obj);
      sprite_obj->get_sprite_resource().load_resource(fes_sprite_obj->get_sprite_path(), sprite_obj);
      break;
    }
    case fes::PointLightObject: {
      const auto& fes_pt_obj = std::static_pointer_cast<fes::FesPointLightObjectAST>(fes_obj);
      const auto& pt_obj = std::static_pointer_cast<fresh::PointLightObject>(gen_obj);
      {
        const auto& ambient = fes_pt_obj->get_ambient()->get_color();
        const auto& diffuse = fes_pt_obj->get_diffuse()->get_color();
        const auto att_constant = fes_pt_obj->get_attenuation_constant();
        const auto att_linear = fes_pt_obj->get_attenuation_linear();
        const auto att_quadratic = fes_pt_obj->get_attenuation_quadratic();
        pt_obj->get_point_light().set_ambient(glm::vec3 {
            ambient.get_red(),
            ambient.get_green(),
            ambient.get_blue()
        });
        pt_obj->get_point_light().set_diffuse(glm::vec3 {
            diffuse.get_red(),
            diffuse.get_green(),
            diffuse.get_blue()
        });
        pt_obj->get_point_light().set_attenuation_constant(att_constant);
        pt_obj->get_point_light().set_attenuation_linear(att_linear);
        pt_obj->get_point_light().set_attenuation_quadratic(att_quadratic);
      }
      break;
    }
    case fes::CircleObject: {
      const auto& fes_circle_obj =
          std::static_pointer_cast<fes::FesCircleObjectAST>(fes_obj);
      const auto& circle_obj =
          std::static_pointer_cast<fresh::CircleObject>(gen_obj);
      circle_obj->get_circle_resource() = fes_circle_obj->get_resource();
      break;
    }
    case fes::PolygonObject: {
      const auto& fes_polygon_obj = std::static_pointer_cast<fes::FesPolygonObjectAST>(fes_obj);
      const auto& poly_obj = std::static_pointer_cast<fresh::PolygonObject>(gen_obj);
      auto& vertices = poly_obj->get_polygon_resource().get_polygons();
      for(const auto& vert: fes_polygon_obj->get_resource_mutable()) {
        vertices.push_back(vert->get_resource_mutable());
      }
      break;
    }
    case fes::CircleAreaObject: {
      const auto& fes_circle_obj =
          std::static_pointer_cast<fes::FesCircleAreaObjectAST>(fes_obj);
      const auto& circle_obj =
          std::static_pointer_cast<fresh::CircleAreaObject>(gen_obj);
      circle_obj->get_circle_resource() = fes_circle_obj->get_resource();
      break;
    }
    case fes::PolygonAreaObject: {
      const auto& fes_polygon_obj = std::static_pointer_cast<fes::FesPolygonAreaObjectAST>(fes_obj);
      const auto& poly_obj = std::static_pointer_cast<fresh::PolygonAreaObject>(gen_obj);
      auto& vertices = poly_obj->get_polygon_resource().get_polygons();
      for(const auto& vert: fes_polygon_obj->get_resource_mutable()) {
        vertices.push_back(vert->get_resource_mutable());
      }
      break;
    }
  }
  gen_obj->reset_delta();
  for (const auto& child_obj: fes_obj->get_sub_groups()) {
    gen_obj->push_object(std::move(this->generate_from_ast(child_obj)));
    gen_obj->reset_delta();
  }
  return std::move(gen_obj);
}

[[nodiscard]] std::shared_ptr<fes::FesObjectAST>
FesLoaderResource::generate_from_object(
    const std::shared_ptr<BaseObject>& fresh_obj) noexcept {
  auto fes_object =
      std::move(FesLoaderResource::_create_fes_object(fresh_obj->to_string()));
  if (!fes_object) {
    log_error(src(), "invalid object.");
    return nullptr;
  }
  _set_fesobject_properties(fresh_obj, fes_object);
  switch (fes_object->get_type()) {
    case fes::LabelObject: {
      const auto& gen_fes_obj =
          std::static_pointer_cast<fes::FesLabelObjectAST>(fes_object);
      const auto& gen_obj = std::static_pointer_cast<LabelObject>(fresh_obj);
      gen_fes_obj->get_bg_color()->set_color(gen_obj->get_background_color());
      gen_fes_obj->get_fg_color()->set_color(gen_obj->get_foreground_color());
      gen_fes_obj->set_label_text(gen_obj->get_label_text());
      gen_fes_obj->set_font_size(
          gen_obj->get_label_font_resource().get_font_size());
      gen_fes_obj->set_label_path(
          gen_obj->get_label_font_resource().get_font_path());
      break;
    }
    case fes::SpriteObject: {
      const auto& gen_fes_obj =
          std::static_pointer_cast<fes::FesSpriteObjectAST>(fes_object);
      const auto& gen_obj = std::static_pointer_cast<SpriteObject>(fresh_obj);
      gen_fes_obj->set_sprite_path(gen_obj->get_sprite_resource().get_path());
      break;
    }
    case fes::PointLightObject: {
      const auto& gen_fes_obj = std::static_pointer_cast<fes::FesPointLightObjectAST>(fes_object);
      const auto& gen_obj = std::static_pointer_cast<PointLightObject>(fresh_obj);
      gen_fes_obj->get_ambient()->set_color(fresh::ColorResource(
        gen_obj->get_point_light().get_ambient()
      ));
      gen_fes_obj->get_diffuse()->set_color(fresh::ColorResource(
        gen_obj->get_point_light().get_diffuse()
      ));
      gen_fes_obj->set_attenuation_constant(gen_obj->get_point_light().get_attenuation_constant());
      gen_fes_obj->set_attenuation_linear(gen_obj->get_point_light().get_attenuation_linear());
      gen_fes_obj->set_attenuation_quadratic(gen_obj->get_point_light().get_attenuation_quadratic());
      break;
    }
    case fes::CircleObject: {
      const auto& gen_fes_obj =
          std::static_pointer_cast<fes::FesCircleObjectAST>(fes_object);
      const auto& gen_obj = std::static_pointer_cast<CircleObject>(fresh_obj);
      gen_fes_obj->set_resource(gen_obj->get_circle_resource());
      break;
    }
    case fes::PolygonObject: {
      const auto& gen_fes_obj =
          std::static_pointer_cast<fes::FesPolygonObjectAST>(fes_object);
      const auto& gen_obj = std::static_pointer_cast<PolygonObject>(fresh_obj);
      for(const auto& vert: gen_obj->get_polygon_resource().get_polygons()) {
        auto vert_ptr = std::make_shared<fes::FesVertexAST>();
        vert_ptr->set_resource(vert);
        gen_fes_obj->get_resource_mutable().push_back(std::move(vert_ptr));
      }
      break;
    }
    case fes::CircleAreaObject: {
      const auto& gen_fes_obj =
          std::static_pointer_cast<fes::FesCircleAreaObjectAST>(fes_object);
      const auto& gen_obj = std::static_pointer_cast<CircleAreaObject>(fresh_obj);
      gen_fes_obj->set_resource(gen_obj->get_circle_resource());
      break;
    }
    case fes::PolygonAreaObject: {
      const auto& gen_fes_obj =
          std::static_pointer_cast<fes::FesPolygonAreaObjectAST>(fes_object);
      const auto& gen_obj = std::static_pointer_cast<PolygonAreaObject>(fresh_obj);
      for(const auto& vert: gen_obj->get_polygon_resource().get_polygons()) {
        auto vert_ptr = std::make_shared<fes::FesVertexAST>();
        vert_ptr->set_resource(vert);
        gen_fes_obj->get_resource_mutable().push_back(std::move(vert_ptr));
      }
      break;
    }
  }
  for (const auto& child_fes_obj: fresh_obj->get_childs()) {
    fes_object->get_sub_groups().push_back(
        std::move(FesLoaderResource::generate_from_object(child_fes_obj)));
  }
  return std::move(fes_object);
}

[[nodiscard]] std::string FesLoaderResource::serialize(
  const std::shared_ptr<BaseObject>& base_object
) noexcept {
  const auto& convert_fes_obj = FesLoaderResource::generate_from_object(base_object);
  return FesLoaderResource::serialize_object(convert_fes_obj) + ";";
}

[[nodiscard]] std::string FesLoaderResource::serialize_object(
    const std::shared_ptr<fes::FesObjectAST>& fes_obj,
    std::uint32_t whitespace_count) noexcept {
  std::uint32_t local_ws{whitespace_count};
  std::string ctx;
  _serialize_append(ctx, "[", local_ws);
  // TODO: object specific properties.
  switch (fes_obj->get_type()) {
    case fes::Import: // TODO: Import
      ctx.append("Import");
      break;
    case fes::AreaObject:
      ctx.append("AreaObject");
      break;
    case fes::CircleAreaObject:
      ctx.append("CircleAreaObject");
      break;
    case fes::PolygonAreaObject:
      ctx.append("PolygonAreaObject");
      break;
    case fes::RectangleAreaObject:
      ctx.append("RectangleAreaObject");
      break;
    case fes::BaseObject:
      ctx.append("BaseObject");
      break;
    case fes::CircleObject:
      ctx.append("CircleObject");
      break;
    case fes::PolygonObject:
      ctx.append("PolygonObject");
      break;
    case fes::RectangleObject:
      ctx.append("RectangleObject");
      break;
    case fes::CameraObject:
      ctx.append("CameraObject");
      break;
    case fes::LabelObject:
      ctx.append("LabelObject");
      break;
    case fes::SpriteObject:
      ctx.append("SpriteObject");
      break;
    case fes::PointLightObject:
      ctx.append("PointLightObject");
      break;
    case fes::Vertex:
      ctx.append("Vertex");
      break;
    case fes::Color:
      ctx.append("Color");
      break;
  }
  ctx.append(",\n");
  ++local_ws;
  const auto& obj_type = fes_obj->get_type();
  switch(obj_type) {
    case fes::Import: {
      const auto& imp = std::static_pointer_cast<fes::FesImportObjectAST>(fes_obj);
      _serialize_append(ctx, "path = \"" + imp->get_import_path() + "\";", local_ws, true);
      break;
    }
    case fes::Vertex: {
      // Vertex objects are only take position_x and position_y.
      const auto& vert = std::static_pointer_cast<fes::FesVertexAST>(fes_obj);
      _serialize_append(
        ctx,
        "position_x = " + std::to_string(vert->get_resource().get_x()) + ",",
        local_ws, true);
      _serialize_append(
          ctx,
          "position_y = " + std::to_string(vert->get_resource().get_y()) + ";",
          local_ws, true);
      break;
    }
    case fes::Color: {
      // Color objects are only take red, green, blue and alpha.
      const auto& color = std::static_pointer_cast<fes::FesColorObjectAST>(fes_obj);
      _serialize_append(ctx, "red = " + std::to_string(color->get_color().get_red()) + ",", local_ws, true);
      _serialize_append(ctx, "green = " + std::to_string(color->get_color().get_green()) + ",", local_ws, true);
      _serialize_append(ctx, "blue = " + std::to_string(color->get_color().get_blue()) + ",", local_ws, true);
      _serialize_append(ctx, "alpha = " + std::to_string(color->get_color().get_alpha()) + ";", local_ws, true);
      break;
    }
    default: {
      _serialize_append(ctx, "name = \"" + fes_obj->get_name() + "\",", local_ws,
                      true);
      _serialize_append(ctx, "group_id = auto,", local_ws, true);
      _serialize_append(ctx,
                        "disabled = " + _bool_to_str(fes_obj->get_disabled()) + ",",
                        local_ws, true);
      _serialize_append(ctx,
                        "visible = " + _bool_to_str(fes_obj->get_visible()) + ",",
                        local_ws, true);
      _serialize_append(
          ctx, "width = " + std::to_string(fes_obj->get_size().get_w()) + ",",
          local_ws, true);
      _serialize_append(
          ctx, "height = " + std::to_string(fes_obj->get_size().get_h()) + ",",
          local_ws, true);
      _serialize_append(
        ctx, "script_resource = \"" + fes_obj->get_fescript_path() + "\",",
        local_ws, true);
      _serialize_append(
        ctx,
        "position_x = " + std::to_string(fes_obj->get_position().get_x()) + ",",
        local_ws, true);
      _serialize_append(
          ctx,
          "position_y = " + std::to_string(fes_obj->get_position().get_y()) + ",",
          local_ws, true);

      {
        auto color_ptr = std::make_shared<fes::FesColorObjectAST>();
        color_ptr->set_color(fes_obj->get_color());
        _serialize_append(ctx, "fg_color = " + serialize_list(std::vector{color_ptr}) + ",", local_ws, true);
      }

      if(fes_obj->get_type() == fes::PolygonObject) {
        const auto& poly_ptr = std::static_pointer_cast<fes::FesPolygonObjectAST>(fes_obj);
        _serialize_append(ctx, "vertices = " + serialize_list(poly_ptr->get_resource_mutable()) + ",",
          local_ws, true);
      } else if(fes_obj->get_type() == fes::PolygonAreaObject) {
        const auto& poly_ptr = std::static_pointer_cast<fes::FesPolygonAreaObjectAST>(fes_obj);
        _serialize_append(ctx, "vertices = " + serialize_list(poly_ptr->get_resource_mutable()) + ",",
          local_ws, true);
      } else if(fes_obj->get_type() == fes::PointLightObject) {
        const auto& pt_ptr = std::static_pointer_cast<fes::FesPointLightObjectAST>(fes_obj);
        _serialize_append(ctx, "ambient = " + serialize_list(std::vector {pt_ptr->get_ambient()}) + ",", local_ws, true);
        _serialize_append(ctx, "diffuse = " + serialize_list(std::vector{pt_ptr->get_diffuse()}) + ",", local_ws, true);
        _serialize_append(ctx, "att_constant = " + std::to_string(pt_ptr->get_attenuation_constant()) + ",", local_ws, true);
        _serialize_append(ctx, "att_linear = " + std::to_string(pt_ptr->get_attenuation_linear()) + ",", local_ws, true);
        _serialize_append(ctx, "att_quadratic = " + std::to_string(pt_ptr->get_attenuation_quadratic()) + ",", local_ws, true);
      }

      _serialize_append(
            ctx,
            "sub_groups = " + FesLoaderResource::serialize_list(fes_obj->get_sub_groups()) + ";", local_ws, true);
      break;
    }
  }

  --local_ws;
  _serialize_append(ctx, "]", local_ws);
  return ctx;
}

template<typename T>
[[nodiscard]] std::string FesLoaderResource::serialize_list(
    const std::vector<std::shared_ptr<T>>& fes_obj,
    std::uint32_t whitespace_count) noexcept {
  std::uint32_t local_ws{whitespace_count};
  std::string ctx;

  if (!fes_obj.empty()) {
    _serialize_append(ctx, "{", local_ws, true);
    ++local_ws;
    ++local_ws;

    for (std::size_t child_i = 0; child_i < fes_obj.size(); ++child_i) {
      ctx.append(
          FesLoaderResource::serialize_object(fes_obj[child_i], local_ws));
      if (child_i + 1 == fes_obj.size()) {
        ctx.append(";\n");
      } else {
        ctx.append(",\n");
      }
    }

    --local_ws;
    _serialize_append(ctx, "}", local_ws, false);
    --local_ws;
  } else {
    _serialize_append(ctx, "{}", local_ws, false);
  }
  return ctx;
}

void FesLoaderResource::_set_baseobject_properties(
  const std::shared_ptr<fes::FesObjectAST>& fes_obj,
  const std::shared_ptr<BaseObject>& fresh_obj
) noexcept {
  if(fes_obj->get_name().empty()) {
    log_warning(src(), "do not left name empty.");
    fresh_obj->set_name(fresh_obj->to_string() + std::to_string(FesLoaderResource::id_counter));
  } else {
    fresh_obj->set_name(fes_obj->get_name());
  }
  fresh_obj->lazy_set_disabled(fes_obj->get_disabled());
  fresh_obj->lazy_set_visible(fes_obj->get_visible());
  fresh_obj->lazy_set_x(fes_obj->get_position().get_x());
  fresh_obj->lazy_set_y(fes_obj->get_position().get_y());
  fresh_obj->lazy_set_w(fes_obj->get_size().get_w());
  fresh_obj->lazy_set_h(fes_obj->get_size().get_h());
  fresh_obj->set_color(fes_obj->get_color());
  fresh_obj->_object_id = FesLoaderResource::id_counter;
  ++FesLoaderResource::id_counter;
  fresh_obj->load_fescript_rt(fes_obj->get_fescript_path(), true);
}

void FesLoaderResource::_set_fesobject_properties(
  const std::shared_ptr<BaseObject>& fresh_obj,
  std::shared_ptr<fes::FesObjectAST>& fes_obj
) noexcept {
  // TODO: Import only takes path property but i think we need name property too
  // as well since in one FesLoaderResource instance, there can be more than
  // one Import that imports same file.
  if(fresh_obj->is_imported_from_somewhere()) {
    fes_obj.reset();
    fes_obj = std::make_shared<fes::FesImportObjectAST>();
    std::static_pointer_cast<fes::FesImportObjectAST>(fes_obj)->set_import_path(
      fresh_obj->imported_from
    );
    return;
  }

  if(fresh_obj->get_name().empty()) {
    fes_obj->set_name(fresh_obj->to_string() + std::to_string(FesLoaderResource::id_counter));
  } else {
    fes_obj->set_name(fresh_obj->get_name());
  }

  fes_obj->set_disabled(fresh_obj->get_disabled());
  fes_obj->set_visible(fresh_obj->get_visible());
  fes_obj->set_position({
    fresh_obj->get_position().get_x(),
    fresh_obj->get_position().get_y()
  });
  fes_obj->set_size({
    fresh_obj->get_position().get_w(),
    fresh_obj->get_position().get_h()
  });
  fes_obj->set_color(fresh_obj->get_color());
  fes_obj->set_group_id(-1);
  fes_obj->set_fescript_path(fresh_obj->get_fescript_path());
}

[[nodiscard]] std::shared_ptr<BaseObject> FesLoaderResource::_create_object(
    fes::Keywords kw) noexcept {
  switch (kw) {
    case fes::AreaObject:
      return std::make_shared<fresh::AreaObject>();
    case fes::CircleAreaObject:
      return std::make_shared<fresh::CircleAreaObject>();
    case fes::PolygonAreaObject:
      return std::make_shared<fresh::PolygonAreaObject>();
    case fes::RectangleAreaObject:
      return std::make_shared<fresh::RectangleAreaObject>();
    case fes::BaseObject:
      return std::make_shared<fresh::BaseObject>();
    case fes::CircleObject:
      return std::make_shared<fresh::CircleObject>();
    case fes::PolygonObject:
      return std::make_shared<fresh::PolygonObject>();
    case fes::RectangleObject:
      return std::make_shared<fresh::RectangleObject>();
    case fes::CameraObject:
      return std::make_shared<fresh::CameraObject>();
    case fes::LabelObject:
      return std::make_shared<fresh::LabelObject>();
    case fes::SpriteObject:
      return std::make_shared<fresh::SpriteObject>();
    case fes::PointLightObject:
      return std::make_shared<fresh::PointLightObject>();
    default:
      return nullptr;
  }
}

[[nodiscard]] std::shared_ptr<fes::FesObjectAST>
FesLoaderResource::_create_fes_object(const char* fresh_kw) noexcept {
  if (strcmp(fresh_kw, "areaobject") == SameCstr)
    return std::make_shared<fes::FesAreaObjectAST>();
  if (strcmp(fresh_kw, "circleareaobject") == SameCstr)
    return std::make_shared<fes::FesCircleAreaObjectAST>();
  if (strcmp(fresh_kw, "polygonareaobject") == SameCstr)
    return std::make_shared<fes::FesPolygonAreaObjectAST>();
  if (strcmp(fresh_kw, "rectangleareaobject") == SameCstr)
    return std::make_shared<fes::FesRectangleAreaObject>();
  if (strcmp(fresh_kw, "baseobject") == SameCstr)
    return std::make_shared<fes::FesObjectAST>();
  if (strcmp(fresh_kw, "circleobject") == SameCstr)
    return std::make_shared<fes::FesCircleObjectAST>();
  if (strcmp(fresh_kw, "polygonobject") == SameCstr)
    return std::make_shared<fes::FesPolygonObjectAST>();
  if (strcmp(fresh_kw, "rectangleobject") == SameCstr)
    return std::make_shared<fes::FesRectangleObjectAST>();
  if (strcmp(fresh_kw, "cameraobject") == SameCstr)
    return std::make_shared<fes::FesCameraObjectAST>();
  if (strcmp(fresh_kw, "labelobject") == SameCstr)
    return std::make_shared<fes::FesLabelObjectAST>();
  if (strcmp(fresh_kw, "spriteobject") == SameCstr)
    return std::make_shared<fes::FesSpriteObjectAST>();
  if (strcmp(fresh_kw, "pointlightobject") == SameCstr)
    return std::make_shared<fes::FesPointLightObjectAST>();
  // TODO: Import
  return nullptr;
}

void FesLoaderResource::_serialize_append(
  std::string& ctx,
  const std::string& input,
  std::uint32_t whitespace_count,
  bool newline
) noexcept {
  ctx.append(FesLoaderResource::_whitespace_generate(whitespace_count) + input);
  if(newline) {
    ctx.push_back('\n');
  }
}

[[nodiscard]] std::string FesLoaderResource::_whitespace_generate(
    std::uint32_t whitespace_count) noexcept {
  // TODO: use unordered_map here to cache strings
  std::string ws_gen;
  while (whitespace_count > 0) {
    ws_gen.push_back(' ');
    --whitespace_count;
  }
  return ws_gen;
}

[[nodiscard]] std::string FesLoaderResource::_bool_to_str(bool input) noexcept {
  return input ? "true" : "false";
}

template [[nodiscard]] std::string FesLoaderResource::serialize_list<fes::FesObjectAST>(
  const std::vector<std::shared_ptr<fes::FesObjectAST>>&,
  std::uint32_t whitespace_count
) noexcept;

template [[nodiscard]] std::string FesLoaderResource::serialize_list<fes::FesVertexAST>(
  const std::vector<std::shared_ptr<fes::FesVertexAST>>&,
  std::uint32_t whitespace_count
) noexcept;

template [[nodiscard]] std::string FesLoaderResource::serialize_list<fes::FesColorObjectAST>(
  const std::vector<std::shared_ptr<fes::FesColorObjectAST>>&,
  std::uint32_t whitespace_count
) noexcept;
} // namespace fresh