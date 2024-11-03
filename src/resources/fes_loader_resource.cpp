#include <freshengine.hpp>
#include <resources/fes_loader_resource.hpp>
#include <string>
#include <filesystem>

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
    const std::shared_ptr<fes::FesObjectAST>& fes_obj) noexcept {
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

  FesLoaderResource::_set_baseobject_properties(fes_obj, gen_obj);
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
      const auto& fes_sprite_obj =
          std::static_pointer_cast<fes::FesSpriteObjectAST>(fes_obj);
      const auto& sprite_obj =
          std::static_pointer_cast<fresh::SpriteObject>(gen_obj);
      sprite_obj->get_sprite_resource().load_resource(
          fes_sprite_obj->get_sprite_path());
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
  FesLoaderResource::_set_fesobject_properties(fresh_obj, fes_object);
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
      break;
    case fes::AreaObject:
      ctx.append("AreaObject");
      break;
    case fes::BaseObject:
      ctx.append("BaseObject");
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
  }
  ctx.append(",\n");
  ++local_ws;
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
      ctx,
      "position_x = " + std::to_string(fes_obj->get_position().get_x()) + ",",
      local_ws, true);
  _serialize_append(
      ctx,
      "position_y = " + std::to_string(fes_obj->get_position().get_y()) + ",",
      local_ws, true);
  _serialize_append(
      ctx, "script_resource = \"" + fes_obj->get_fescript_path() + "\",",
      local_ws, true);
  _serialize_append(
      ctx,
      "sub_groups = " + FesLoaderResource::serialize_list(fes_obj->get_sub_groups()) + ";", local_ws, true);
  --local_ws;
  _serialize_append(ctx, "]", local_ws);
  return ctx;
}

[[nodiscard]] std::string FesLoaderResource::serialize_list(
    const std::vector<std::shared_ptr<fes::FesObjectAST>>& fes_obj,
    std::uint32_t whitespace_count) noexcept {
  std::uint32_t local_ws{whitespace_count};
  std::string ctx;

  if(!fes_obj.empty()) {
    _serialize_append(ctx, "{", local_ws, true);
    ++local_ws;
    ++local_ws;

    for (std::size_t child_i = 0; child_i < fes_obj.size(); ++child_i) {
      ctx.append(FesLoaderResource::serialize_object(fes_obj[child_i], local_ws));
      if(child_i + 1 == fes_obj.size()) {
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
    log_warning(src(), "do not left empty name empty.");
    fresh_obj->set_name(fresh_obj->to_string() + std::to_string(FesLoaderResource::id_counter));
  } else {
    fresh_obj->set_name(fes_obj->get_name());
  }
  fresh_obj->set_disabled(fes_obj->get_disabled());
  fresh_obj->set_visible(fes_obj->get_visible());
  fresh_obj->set_x(fes_obj->get_position().get_x());
  fresh_obj->set_y(fes_obj->get_position().get_y());
  fresh_obj->set_w(fes_obj->get_size().get_w());
  fresh_obj->set_h(fes_obj->get_size().get_h());
  fresh_obj->_object_id = FesLoaderResource::id_counter;
  ++FesLoaderResource::id_counter;
  fresh_obj->load_fescript_rt(fes_obj->get_fescript_path(), true);
}

void FesLoaderResource::_set_fesobject_properties(
  const std::shared_ptr<BaseObject>& fresh_obj,
  const std::shared_ptr<fes::FesObjectAST>& fes_obj
) noexcept {
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
  fes_obj->set_group_id(-1);
  fes_obj->set_fescript_path(fresh_obj->get_fescript_path());
}

[[nodiscard]] std::shared_ptr<BaseObject> FesLoaderResource::_create_object(
    fes::Keywords kw) noexcept {
  switch (kw) {
    case fes::AreaObject:
      return std::make_shared<fresh::AreaObject>();
    case fes::BaseObject:
      return std::make_shared<fresh::BaseObject>();
    case fes::CameraObject:
      return std::make_shared<fresh::CameraObject>();
    case fes::LabelObject:
      return std::make_shared<fresh::LabelObject>();
    case fes::SpriteObject:
      return std::make_shared<fresh::SpriteObject>();
    default:
      return nullptr;
  }
}

[[nodiscard]] std::shared_ptr<fes::FesObjectAST>
FesLoaderResource::_create_fes_object(const char* fresh_kw) noexcept {
  if (fresh_kw == "areaobject")
    return std::make_shared<fes::FesAreaObjectAST>();
  if (fresh_kw == "baseobject")
    return std::make_shared<fes::FesObjectAST>();
  if (fresh_kw == "cameraobject")
    return std::make_shared<fes::FesCameraObjectAST>();
  if (fresh_kw == "labelobject")
    return std::make_shared<fes::FesLabelObjectAST>();
  if (fresh_kw == "spriteobject")
    return std::make_shared<fes::FesSpriteObjectAST>();
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
} // namespace fresh