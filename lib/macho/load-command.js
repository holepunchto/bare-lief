const binding = require('#binding')

module.exports = class MachOLoadCommand {
  constructor(opts = {}) {
    const { handle } = opts

    this._handle = handle
  }

  get data() {
    return Buffer.from(binding.machOLoadCommandGetData(this._handle).buffer)
  }

  set data(value) {
    binding.machOLoadCommandSetData(this._handle, value)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: MachOLoadCommand },

      data: this.data
    }
  }
}
