#include <assert.h>
#include <bare.h>
#include <js.h>
#include <jstl.h>
#include <stddef.h>
#include <stdint.h>

#include "lib/elf.h"
#include "lib/macho.h"

static js_value_t *
bare_lief_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  err = js_set_property<fn>(env, exports, name); \
  assert(err == 0);

  // MachO
  V("machOBinaryAddSegment", bare_lief_macho_binary_add_segment)
  V("machOFatBinaryParse", bare_lief_macho_fat_binary_parse)
  V("machOFatBinaryWrite", bare_lief_macho_fat_binary_write)
  V("machOFatBinaryGetRaw", bare_lief_macho_fat_binary_get_raw)
  V("machOFatBinaryGetSize", bare_lief_marcho_fat_binary_get_size)
  V("machOFatBinaryGetAt", bare_lief_macho_fat_binary_get_at)
  V("machOSectionCreate", bare_lief_macho_section_create)
  V("machOSegmentCommandCreate", bare_lief_macho_segment_command_create)
  V("machOSegmentCommandAddSection", bare_lief_mecho_segment_command_add_section)

  // ELF
  V("elfBinaryParse", bare_lief_elf_binary_parse)
#undef V

  return exports;
}

BARE_MODULE(bare_lief, bare_lief_exports)
