const binding = require('#binding')
const MachOBinary = require('./binary')

module.exports = class MachOFatBinary {
  constructor(input) {
    this._binaries = []

    this._handle = binding.parseMachO(input)

    for (let i = 0, n = binding.getMachOBinarySize(this._handle); i < n; i++) {
      this._binaries.push(new MachOBinary(binding.getMachOBinaryAt(this._handle, i)))
    }
  }

  get size() {
    return this._binaries.length
  }

  at(i) {
    return this._binaries[i]
  }

  write(path) {
    binding.writeMachO(this._handle, path)
  }

  toBuffer() {
    return Buffer.from(binding.getRawMachO(this._handle))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: MachOFatBinary },

      binaries: this._binaries
    }
  }
}
