#pragma once

#include <memory>
#include <optional>

#include <assert.h>
#include <bare.h>
#include <js.h>
#include <jstl.h>
#include <stddef.h>
#include <stdint.h>

#include <LIEF/MachO.hpp>

#include "handle.h"

using namespace LIEF;

static std::shared_ptr<bare_lief_handle_t<MachO::FatBinary>>
bare_lief_macho_fat_binary_parse(
  js_env_t *,
  js_receiver_t,
  std::span<uint8_t> buffer
) {
  return std::make_shared<bare_lief_handle_t<MachO::FatBinary>>(
    MachO::Parser::parse(std::vector(buffer.begin(), buffer.end())).release()
  );
}

static void
bare_lief_macho_fat_binary_write(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<MachO::FatBinary>> binary,
  std::string path
) {
  binary->handle->write(path);
}

static js_arraybuffer_t
bare_lief_macho_fat_binary_get_raw(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<MachO::FatBinary>> binary
) {
  int err;

  auto buffer = binary->handle->raw();

  js_arraybuffer_t result;
  err = js_create_arraybuffer(env, buffer, result);
  assert(err == 0);

  return result;
}

static int64_t
bare_lief_marcho_fat_binary_get_size(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<MachO::FatBinary>> binary
) {
  return binary->handle->size();
}

static std::optional<std::shared_ptr<bare_lief_handle_t<MachO::Binary>>>
bare_lief_macho_fat_binary_get_at(
  js_env_t *env,
  js_receiver_t,
  js_object_t self,
  std::shared_ptr<bare_lief_handle_t<MachO::FatBinary>> binary,
  int64_t i
) {
  int err;

  auto handle = binary->handle->at(i);

  if (handle == nullptr) return std::nullopt;

  js_persistent_t<js_object_t> owner;
  err = js_create_reference(env, self, owner);
  assert(err == 0);

  return std::make_shared<bare_lief_handle_t<MachO::Binary>>(handle, std::move(owner));
}

static std::shared_ptr<bare_lief_handle_t<MachO::Section>>
bare_lief_macho_section_create(
  js_env_t *,
  js_receiver_t,
  std::string name,
  std::span<uint8_t> buffer
) {
  auto handle = new MachO::Section(name, std::vector(buffer.begin(), buffer.end()));

  return std::make_shared<bare_lief_handle_t<MachO::Section>>(handle);
}

static std::shared_ptr<bare_lief_handle_t<MachO::SegmentCommand>>
bare_lief_macho_segment_command_create(
  js_env_t *,
  js_receiver_t,
  std::string name
) {
  auto handle = new MachO::SegmentCommand(name);

  return std::make_shared<bare_lief_handle_t<MachO::SegmentCommand>>(handle);
}

static void
bare_lief_mecho_segment_command_add_section(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<MachO::SegmentCommand>> segment,
  std::shared_ptr<bare_lief_handle_t<MachO::Section>> section
) {
  segment->handle->add_section(*section->handle);
}

static void
bare_lief_macho_binary_add_segment(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<MachO::Binary>> binary,
  std::shared_ptr<bare_lief_handle_t<MachO::SegmentCommand>> segment
) {
  binary->handle->add(*segment->handle);
}
