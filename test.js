const test = require('brittle')
const lief = require('.')

test('MachO', (t) => {
  const exe = require('./test/fixtures/executable/darwin-arm64/exe', {
    with: { type: 'binary' }
  })

  const binary = new lief.MachO.FatBinary(exe)

  t.comment(binary)
  t.ok(binary)

  const section = new lief.MachO.Section('__data', Buffer.from('hello world'))

  const segment = new lief.MachO.SegmentCommand('__PAYLOAD')
  segment.addSection(section)

  binary.at(0).addSegment(segment)
})
