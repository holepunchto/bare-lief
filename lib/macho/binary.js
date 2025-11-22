const binding = require('#binding')

module.exports = class MachOBinary {
  constructor(handle) {
    this._handle = handle
  }

  addSegment(segment) {
    binding.addMachOSegment(this._handle, segment._handle)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: MachOBinary }
    }
  }
}
