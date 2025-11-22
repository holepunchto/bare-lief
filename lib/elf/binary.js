const binding = require('#binding')

module.exports = class ELFBinary {
  constructor(input) {
    this._handle = binding.elfBinaryParse(input)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: ELFBinary }
    }
  }
}
