const assert = require('assert')
const binding = require('#binding')

module.exports = class PEImport {
  constructor(opts = {}) {
    const { handle } = opts

    this._handle = handle
  }

  get name() {
    assert(this._handle)

    return binding.peImportGetName(this._handle)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: PEImport },

      name: this.name
    }
  }
}
