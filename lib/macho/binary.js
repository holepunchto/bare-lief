const binding = require('#binding')

module.exports = class MachOBinary {
  constructor(opts = {}) {
    const { handle } = opts

    this._handle = handle
  }

  addSegment(segment) {
    binding.machOBinaryAddSegment(this._handle, segment._handle)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: MachOBinary }
    }
  }
}
