const test = require('brittle')
const { MachO, ELF } = require('.')

test('MachO executable, parse arm64', (t) => {
  const exe = require('./test/fixtures/executable/darwin-arm64/exe', {
    with: { type: 'binary' }
  })

  const binary = MachO.FatBinary.parse(exe)

  t.comment(binary)
  t.ok(binary)
})

test('MachO executable, parse x64', (t) => {
  const exe = require('./test/fixtures/executable/darwin-x64/exe', {
    with: { type: 'binary' }
  })

  const binary = MachO.FatBinary.parse(exe)

  t.comment(binary)
  t.ok(binary)
})

test('MachO executable, merge arm64 and x64', (t) => {
  const arm64 = require('./test/fixtures/executable/darwin-arm64/exe', {
    with: { type: 'binary' }
  })

  const x64 = require('./test/fixtures/executable/darwin-x64/exe', {
    with: { type: 'binary' }
  })

  const binary = MachO.FatBinary.merge([MachO.FatBinary.parse(arm64), MachO.FatBinary.parse(x64)])

  t.comment(binary)
  t.ok(binary)
})

test('MachO shared library, parse arm64', (t) => {
  const exe = require('./test/fixtures/shared-library/darwin-arm64/liblib.dylib', {
    with: { type: 'binary' }
  })

  const binary = MachO.FatBinary.parse(exe)

  t.comment(binary)
  t.ok(binary)
})

test('ELF executable, parse arm64', (t) => {
  const exe = require('./test/fixtures/executable/linux-arm64/exe', {
    with: { type: 'binary' }
  })

  const binary = ELF.Binary.parse(exe)

  t.comment(binary)
  t.ok(binary)
})

test('ELF shared library, parse arm64', (t) => {
  const lib = require('./test/fixtures/shared-library/linux-arm64/liblib.so', {
    with: { type: 'binary' }
  })

  const binary = ELF.Binary.parse(lib)

  t.comment(binary)
  t.ok(binary)
})
