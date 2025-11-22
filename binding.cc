#include <memory>
#include <optional>

#include <assert.h>
#include <bare.h>
#include <js.h>
#include <jstl.h>
#include <stddef.h>
#include <stdint.h>

#include <LIEF/MachO.hpp>

static std::shared_ptr<LIEF::MachO::FatBinary>
bare_lief_parse_macho(
  js_env_t *,
  js_receiver_t,
  std::span<uint8_t> buffer
) {
  return LIEF::MachO::Parser::parse(std::vector(buffer.begin(), buffer.end()));
}

static void
bare_lief_write_macho(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<LIEF::MachO::FatBinary> binary,
  std::string path
) {
  binary->write(path);
}

static js_arraybuffer_t
bare_lief_get_raw_macho(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<LIEF::MachO::FatBinary> binary
) {
  int err;

  auto buffer = binary->raw();

  js_arraybuffer_t result;
  err = js_create_arraybuffer(env, buffer, result);
  assert(err == 0);

  return result;
}

static int64_t
bare_lief_get_macho_binary_size(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<LIEF::MachO::FatBinary> binary
) {
  return binary->size();
}

static std::optional<LIEF::MachO::Binary *>
bare_lief_get_macho_binary_at(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<LIEF::MachO::FatBinary> binary,
  int64_t i
) {
  return i < binary->size() ? std::optional(binary->at(i)) : std::nullopt;
}

static std::shared_ptr<LIEF::MachO::Section>
bare_lief_create_macho_section(
  js_env_t *,
  js_receiver_t,
  std::string name,
  std::span<uint8_t> buffer
) {
  return std::make_shared<LIEF::MachO::Section>(name, std::vector(buffer.begin(), buffer.end()));
}

static std::shared_ptr<LIEF::MachO::SegmentCommand>
bare_lief_create_macho_segment_command(
  js_env_t *,
  js_receiver_t,
  std::string name
) {
  return std::make_shared<LIEF::MachO::SegmentCommand>(name);
}

static void
bare_lief_add_macho_segment_section(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<LIEF::MachO::SegmentCommand> segment,
  std::shared_ptr<LIEF::MachO::Section> section
) {
  segment->add_section(*section);
}

static void
bare_lief_add_macho_segment(
  js_env_t *,
  js_receiver_t,
  LIEF::MachO::Binary *binary,
  std::shared_ptr<LIEF::MachO::SegmentCommand> segment
) {
  binary->add(*segment);
}

static js_value_t *
bare_lief_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  err = js_set_property<fn>(env, exports, name); \
  assert(err == 0);

  V("parseMachO", bare_lief_parse_macho)
  V("writeMachO", bare_lief_write_macho)
  V("getRawMachO", bare_lief_get_raw_macho)
  V("getMachOBinarySize", bare_lief_get_macho_binary_size)
  V("getMachOBinaryAt", bare_lief_get_macho_binary_at)
  V("createMachOSection", bare_lief_create_macho_section)
  V("createMachOSegmentCommand", bare_lief_create_macho_segment_command)
  V("addMachOSegmentSection", bare_lief_add_macho_segment_section)
  V("addMachOSegment", bare_lief_add_macho_segment)
#undef V

  return exports;
}

BARE_MODULE(bare_lief, bare_lief_exports)
