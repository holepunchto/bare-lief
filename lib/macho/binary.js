const binding = require('#binding')

module.exports = class MachOBinary {
  constructor(opts = {}) {
    const { handle, owner = null } = opts

    this._handle = handle
    this._owner = owner
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
