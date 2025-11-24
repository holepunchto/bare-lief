const binding = require('#binding')

module.exports = {
  macho: {
    loadCommand: {
      ID_DYLIB: binding.MACHO_LOAD_COMMAND_ID_DYLIB,
      RPATH: binding.MACHO_LOAD_COMMAND_RPATH
    }
  },
  elf: {
    dynamicEntry: {
      NEEDED: binding.ELF_DYNAMIC_ENTRY_NEEDED,
      SONAME: binding.ELF_DYNAMIC_ENTRY_SONAME,
      RUNPATH: binding.ELF_DYNAMIC_ENTRY_RUNPATH
    }
  }
}
