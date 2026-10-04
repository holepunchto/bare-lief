const assert = require('assert')
const binding = require('#binding')

module.exports = class PEDelayImport {
  constructor(opts = {}) {
    const { handle } = opts

    this._handle = handle
  }

  get name() {
    assert(this._handle)

    return binding.peDelayImportGetName(this._handle)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: PEDelayImport },

      name: this.name
    }
  }
}
