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

using namespace LIEF;

static std::shared_ptr<MachO::FatBinary>
bare_lief_macho_fat_binary_parse(
  js_env_t *,
  js_receiver_t,
  std::span<uint8_t> buffer
) {
  return MachO::Parser::parse(std::vector(buffer.begin(), buffer.end()));
}

static void
bare_lief_macho_fat_binary_write(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<MachO::FatBinary> binary,
  std::string path
) {
  binary->write(path);
}

static js_arraybuffer_t
bare_lief_macho_fat_binary_get_raw(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<MachO::FatBinary> binary
) {
  int err;

  auto buffer = binary->raw();

  js_arraybuffer_t result;
  err = js_create_arraybuffer(env, buffer, result);
  assert(err == 0);

  return result;
}

static int64_t
bare_lief_marcho_fat_binary_get_size(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<MachO::FatBinary> binary
) {
  return binary->size();
}

static std::optional<MachO::Binary *>
bare_lief_macho_fat_binary_get_at(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<MachO::FatBinary> binary,
  int64_t i
) {
  return i < binary->size() ? std::optional(binary->at(i)) : std::nullopt;
}

static std::shared_ptr<MachO::Section>
bare_lief_macho_section_create(
  js_env_t *,
  js_receiver_t,
  std::string name,
  std::span<uint8_t> buffer
) {
  return std::make_shared<MachO::Section>(name, std::vector(buffer.begin(), buffer.end()));
}

static std::shared_ptr<MachO::SegmentCommand>
bare_lief_macho_segment_command_create(
  js_env_t *,
  js_receiver_t,
  std::string name
) {
  return std::make_shared<MachO::SegmentCommand>(name);
}

static void
bare_lief_mecho_segment_command_add_section(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<MachO::SegmentCommand> segment,
  std::shared_ptr<MachO::Section> section
) {
  segment->add_section(*section);
}

static void
bare_lief_macho_binary_add_segment(
  js_env_t *,
  js_receiver_t,
  MachO::Binary *binary,
  std::shared_ptr<MachO::SegmentCommand> segment
) {
  binary->add(*segment);
}
