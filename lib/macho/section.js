const assert = require('assert')
const binding = require('#binding')

module.exports = class MachOSection {
  constructor(name, content) {
    if (typeof name === 'object' && name !== null) {
      this._name = null
      this._handle = name.handle
      return
    }

    assert.equal(typeof name, 'string')
    assert(ArrayBuffer.isView(content))

    this._name = name

    this._handle = binding.machOSectionCreate(name, content)
  }

  get content() {
    assert(this._handle)

    return Buffer.from(binding.machOSectionGetContent(this._handle))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: MachOSection },

      name: this._name
    }
  }
}
