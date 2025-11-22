const binding = require('#binding')
const ELFDynamicEntry = require('./dynamic-entry')

module.exports = class ELFBinary {
  constructor(input) {
    this._handle = binding.elfBinaryParse(input)
  }

  getDynamicEntry(tag) {
    const handle = binding.elfBinaryGetDynamicEntry(this, this._handle, tag)

    if (handle === undefined) return null

    return new ELFDynamicEntry({ handle })
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: ELFBinary }
    }
  }
}
