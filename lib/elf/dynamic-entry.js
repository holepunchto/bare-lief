const binding = require('#binding')

class ELFDynamicEntry {
  constructor(opts = {}) {
    const { handle, owner = null } = opts

    this._handle = handle
    this._owner = owner
  }

  asSharedObject() {
    return new ELFDynamicSharedObject({ handle: this._handle, owner: this._owner })
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

    const { handle = binding.elfDynamicSharedObjectCreate(name), owner = null } = opts

    super({ handle, owner })
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
