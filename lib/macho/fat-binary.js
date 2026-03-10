const binding = require('#binding')
const MachOBinary = require('./binary')

module.exports = class MachOFatBinary {
  constructor(binaries, opts = {}) {
    if (typeof binaries === 'object' && binaries !== null && !Array.isArray(binaries)) {
      opts = binaries
      binaries = null
    }

    const { handle = binding.machOFatBinaryCreate(binaries.map(takeBinaries)) } = opts

    this._binaries = []
    this._handle = handle

    for (let i = 0, n = binding.machOFatBinaryGetSize(this._handle); i < n; i++) {
      this._binaries.push(
        new MachOBinary({ handle: binding.machOFatBinaryGetAt(this, this._handle, i) })
      )
    }
  }

  get size() {
    return this._binaries.length
  }

  at(i) {
    return this._binaries.at(i)
  }

  toDisk(path) {
    binding.machOFatBinaryWrite(this._handle, path)
  }

  toBuffer() {
    return Buffer.from(binding.machOFatBinaryGetRaw(this._handle))
  }

  [Symbol.iterator]() {
    return this._binaries[Symbol.iterator]()
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: MachOFatBinary },

      binaries: this._binaries
    }
  }

  static parse(input) {
    return new MachOFatBinary({
      handle: binding.machOFatBinaryParse(input)
    })
  }

  static merge(binaries) {
    return new MachOFatBinary({
      handle: binding.machOFatBinaryMerge(binaries.map(takeFatBinaries))
    })
  }
}

function takeBinaries(binary) {
  const handle = binary._handle
  binary._handle = null
  return handle
}

function takeFatBinaries(binary) {
  const handle = binary._handle
  binary._handle = null
  binary._binaries = []
  return handle
}
