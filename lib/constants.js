const binding = require('#binding')

module.exports = {
  elf: {
    dynamicEntry: {
      NEEDED: binding.ELF_DYNAMIC_ENTRY_NEEDED,
      SONAME: binding.ELF_DYNAMIC_ENTRY_SONAME,
      RUNPATH: binding.ELF_DYNAMIC_ENTRY_RUNPATH
    }
  }
}
