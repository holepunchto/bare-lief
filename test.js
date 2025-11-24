const test = require('brittle')
const { MachO, ELF, constants } = require('.')

const {
  macho: {
    loadCommand: { ID_DYLIB }
  },
  elf: {
    dynamicEntry: { SONAME }
  }
} = constants

test('MachO executable', (t) => {
  const exe = require('./test/fixtures/executable/darwin-arm64/exe', {
    with: { type: 'binary' }
  })

  const binary = new MachO.FatBinary(exe)

  t.comment(binary)
  t.ok(binary)

  const section = new MachO.Section('__data', Buffer.from('hello world'))

  const segment = new MachO.SegmentCommand('__PAYLOAD')

  segment.addSection(section)

  binary.at(0).addSegmentCommand(segment)
})

test('MachO shared library', (t) => {
  const exe = require('./test/fixtures/shared-library/darwin-arm64/liblib.dylib', {
    with: { type: 'binary' }
  })

  const binary = new MachO.FatBinary(exe)

  t.comment(binary)
  t.ok(binary)
})

test('ELF executable', (t) => {
  const exe = require('./test/fixtures/executable/linux-arm64/exe', {
    with: { type: 'binary' }
  })

  const binary = new ELF.Binary(exe)

  t.comment(binary)
  t.ok(binary)
})

test('ELF shared library', (t) => {
  const lib = require('./test/fixtures/shared-library/linux-arm64/liblib.so', {
    with: { type: 'binary' }
  })

  const binary = new ELF.Binary(lib)

  t.comment(binary)
  t.ok(binary)

  const soname = binary.getDynamicEntry(SONAME)

  t.comment(soname)
})
