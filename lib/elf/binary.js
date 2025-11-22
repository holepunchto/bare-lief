const binding = require('#binding')
const constants = require('../constants')
const ELFDynamicEntry = require('./dynamic-entry')

const {
  elf: {
    dynamicEntry: { SONAME, NEEDED, RUNPATH }
  }
} = constants

module.exports = class ELFBinary {
  constructor(input) {
    this._handle = binding.elfBinaryParse(input)
  }

  addDynamicEntry(entry) {
    binding.elfBinaryAddDynamicEntry(this._handle, entry._handle)
  }

  getDynamicEntry(tag) {
    const handle = binding.elfBinaryGetDynamicEntry(this, this._handle, tag)

    if (handle === undefined) return null

    switch (tag) {
      case SONAME:
        return new ELFDynamicEntry.SharedObject({ handle })
      case NEEDED:
        return new ELFDynamicEntry.Library({ handle })
      case RUNPATH:
        return new ELFDynamicEntry.RunPath({ handle })
      default:
        return new ELFDynamicEntry({ handle })
    }
  }

  hasDynamicEntry(tag) {
    return binding.elfBinaryHasDynamicEntry(this._handle, tag)
  }

  addLibrary(name) {
    binding.elfBinaryAddLibrary(this._handle, name)
  }

  getLibrary(name) {
    const handle = binding.elfBinaryGetLibrary(this, this._handle, name)

    if (handle === undefined) return null

    return new ELFDynamicEntry.Library({ handle })
  }

  hasLibrary(name) {
    return binding.elfBinaryHasLibrary(this._handle, name)
  }

  toDisk(path) {
    binding.elfBinaryWrite(this._handle, path)
  }

  toBuffer() {
    return Buffer.from(binding.elfBinaryGetRaw(this._handle))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: ELFBinary }
    }
  }
}
