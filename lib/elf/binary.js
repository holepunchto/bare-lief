const binding = require('#binding')
const ELFDynamicEntry = require('./dynamic-entry')
const ELFSection = require('./section')

const { TAG } = ELFDynamicEntry

module.exports = class ELFBinary {
  constructor(input) {
    this._handle = binding.elfBinaryParse(input)
  }

  addSection(section, loaded = true) {
    const handle = binding.elfBinaryAddSection(this, this._handle, section._handle, loaded)

    return new ELFSection({ handle })
  }

  getSection(name) {
    const handle = binding.elfBinaryGetSection(this, this._handle, name)

    if (handle === undefined) return null

    return new ELFSection({ handle })
  }

  getSectionIndex(name) {
    return binding.elfBinaryGetSectionIndex(this._handle, name)
  }

  addDynamicSymbol(symbol) {
    binding.elfBinaryAddDynamicSymbol(this._handle, symbol._handle)
  }

  addDynamicEntry(entry) {
    binding.elfBinaryAddDynamicEntry(this._handle, entry._handle)
  }

  getDynamicEntry(tag) {
    const handle = binding.elfBinaryGetDynamicEntry(this, this._handle, tag)

    if (handle === undefined) return null

    switch (tag) {
      case TAG.SONAME:
        return new ELFDynamicEntry.SharedObject({ handle })
      case TAG.NEEDED:
        return new ELFDynamicEntry.Library({ handle })
      case TAG.RUNPATH:
        return new ELFDynamicEntry.RunPath({ handle })
      default:
        return new ELFDynamicEntry({ handle })
    }
  }

  hasDynamicEntry(tag) {
    return binding.elfBinaryHasDynamicEntry(this._handle, tag)
  }

  removeDynamicEntry(entry) {
    binding.elfBinaryRemoveDynamicEntry(this._handle, entry._handle)
  }

  removeAllDynamicEntries(tag) {
    binding.elfBinaryRemoveAllDynamicEntries(this._handle, tag)
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

  removeLibrary(name) {
    binding.elfBinaryRemoveLibrary(this._handle, name)
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
