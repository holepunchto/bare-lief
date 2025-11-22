const binding = require('#binding')

module.exports = class MachOSegmentCommand {
  constructor(name) {
    this._name = name

    this._handle = binding.machOSegmentCommandCreate(this._name)
  }

  addSection(section) {
    binding.machOSegmentCommandAddSection(this._handle, section._handle)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: MachOSegmentCommand },

      name: this._name
    }
  }
}
