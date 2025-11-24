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

  // Mach-O
  V("machOFatBinaryParse", bare_lief_macho_fat_binary_parse)
  V("machOFatBinaryWrite", bare_lief_macho_fat_binary_write)
  V("machOFatBinaryMerge", bare_lief_macho_fat_binary_merge)
  V("machOFatBinaryGetRaw", bare_lief_macho_fat_binary_get_raw)
  V("machOFatBinaryGetSize", bare_lief_marcho_fat_binary_get_size)
  V("machOFatBinaryGetAt", bare_lief_macho_fat_binary_get_at)
  V("machOBinaryAddSegmentCommand", bare_lief_macho_binary_add_segment_command)
  V("machOBinaryGetLoadCommand", bare_lief_macho_binary_get_load_command)
  V("machOBinaryHasLoadCommand", bare_lief_macho_binary_has_load_command)
  V("machOBinaryRemoveLoadCommand", bare_lief_macho_binary_remove_load_command)
  V("machOBinaryAddDylibCommand", bare_lief_macho_binary_add_dylib_command)
  V("machOBinaryFindLibrary", bare_lief_macho_binary_find_library)
  V("machOBinaryAddLibrary", bare_lief_macho_binary_add_library)
  V("machOSectionCreate", bare_lief_macho_section_create)
  V("machOSegmentCommandCreate", bare_lief_macho_segment_command_create)
  V("machOSegmentCommandAddSection", bare_lief_macho_segment_command_add_section)
  V("machOLoadCommandGetData", bare_lief_macho_load_command_get_data)
  V("machOLoadCommandSetData", bare_lief_macho_load_command_set_data)
  V("machODylibCommandCreateID", bare_lief_macho_dylib_command_create_id)
  V("machODylibCommandGetName", bare_lief_macho_dylib_command_get_name)
  V("machODylibCommandSetName", bare_lief_macho_dylib_command_set_name)
  V("machORPathCommandCreate", bare_lief_macho_rpath_command_create)

  // ELF
  V("elfBinaryParse", bare_lief_elf_binary_parse)
  V("elfBinaryWrite", bare_lief_elf_binary_write)
  V("elfBinaryGetRaw", bare_lief_elf_binary_get_raw)
  V("elfBinaryAddDynamicEntry", bare_lief_elf_binary_add_dynamic_entry)
  V("elfBinaryGetDynamicEntry", bare_lief_elf_binary_get_dynamic_entry)
  V("elfBinaryHasDynamicEntry", bare_lief_elf_binary_has_dynamic_entry)
  V("elfBinaryAddLibrary", bare_lief_elf_binary_add_library)
  V("elfBinaryGetLibrary", bare_lief_elf_binary_get_library)
  V("elfBinaryHasLibrary", bare_lief_elf_binary_has_library)
  V("elfBinaryRemoveLibrary", bare_lief_elf_binary_remove_library)
  V("elfDynamicSharedObjectCreate", bare_lief_elf_dynamic_shared_object_create)
  V("elfDynamicSharedObjectGetName", bare_lief_elf_dynamic_shared_object_get_name)
  V("elfDynamicSharedObjectSetName", bare_lief_elf_dynamic_shared_object_set_name)
  V("elfDynamicEntryLibraryCreate", bare_lief_elf_dynamic_entry_library_create)
  V("elfDynamicEntryLibraryGetName", bare_lief_elf_dynamic_entry_library_get_name)
  V("elfDynamicEntryLibrarySetName", bare_lief_elf_dynamic_entry_library_set_name)
  V("elfDynamicEntryRunPathCreate", bare_lief_elf_dynamic_entry_run_path_create)
  V("elfDynamicEntryRunPathGetRunPath", bare_lief_elf_dynamic_entry_run_path_get_run_path)
  V("elfDynamicEntryRunPathSetRunPath", bare_lief_elf_dynamic_entry_run_path_set_run_path)
#undef V

#define V(name, value) \
  err = js_set_property(env, exports, name, int64_t(value)); \
  assert(err == 0);

  // Mach-O
  V("MACHO_LOAD_COMMAND_ID_DYLIB", MachO::LoadCommand::TYPE::ID_DYLIB)
  V("MACHO_LOAD_COMMAND_RPATH", MachO::LoadCommand::TYPE::RPATH)

  // ELF
  V("ELF_DYNAMIC_ENTRY_NEEDED", ELF::DynamicEntry::TAG::NEEDED)
  V("ELF_DYNAMIC_ENTRY_SONAME", ELF::DynamicEntry::TAG::SONAME)
  V("ELF_DYNAMIC_ENTRY_RUNPATH", ELF::DynamicEntry::TAG::RUNPATH)
#undef V

  return exports;
}

BARE_MODULE(bare_lief, bare_lief_exports)
