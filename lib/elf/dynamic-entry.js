const binding = require('#binding')

class ELFDynamicEntry {
  constructor(opts = {}) {
    const { handle } = opts

    this._handle = handle
  }

  asSharedObject() {
    return new ELFDynamicSharedObject({ handle: this._handle })
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: ELFDynamicEntry }
    }
  }
}

module.exports = ELFDynamicEntry

class ELFDynamicSharedObject extends ELFDynamicEntry {
  constructor(name, opts = {}) {
    if (typeof name === 'object' && name !== null) {
      opts = name
      name = null
    }

    const { handle = binding.elfDynamicSharedObjectCreate(name) } = opts

    super({ handle })
  }

  get name() {
    return binding.elfDynamicSharedObjectGetName(this._handle)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: ELFDynamicSharedObject },

      name: this.name
    }
  }
}
