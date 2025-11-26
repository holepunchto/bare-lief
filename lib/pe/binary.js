const binding = require('#binding')
const PESection = require('./section')

module.exports = class PEBinary {
  constructor(input) {
    this._handle = binding.peBinaryParse(input)
  }

  addSection(section) {
    const handle = binding.peBinaryAddSection(this, this._handle, section._handle)

    return new PESection({ handle })
  }

  getSection(name) {
    const handle = binding.peBinaryGetSection(this, this._handle, name)

    if (handle === undefined) return null

    return new PESection({ handle })
  }

  toDisk(path) {
    binding.peBinaryWrite(this._handle, path)
  }

  toBuffer() {
    return Buffer.from(binding.peBinaryGetRaw(this._handle))
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: PEBinary }
    }
  }
}
