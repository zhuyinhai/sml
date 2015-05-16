# coding: utf-8

import codecs
import json
import struct

ENDIAN = '<'
VERSION = (0,1)
SML_HEADER_SIZE = 16
DATA_HEADER_SIZE = 12
OFFSET_ST_SIZE = 8
TEXTURE_ST_SIZE = 40
PLANE_ST_SIZE = 44
SPRITE_ST_SIZE = 60
NINE_SPRITE_ST_SIZE = 76
COMPOSITION_ST_SIZE = 36
LAYER_ST_SIZE = 84
STATE_ST_SIZE = 48
STATE_KEYFRAME_ST_SIZE = 28

def main():

    indata = json.load(codecs.open('test_data.json', 'r', 'utf-8'))

    textures = indata['texture']
    planes = indata['plane']
    sprites = indata['sprite']
    nine_sprites = indata['nine_slice_sprite']
    compositions = indata['composition']
    layers = indata['layer']
    states = indata['state']
    state_keyframes = indata['state_keyframe']


    offsets = [];
    offset = SML_HEADER_SIZE;
    offset += DATA_HEADER_SIZE + OFFSET_ST_SIZE*8
    offsets.append( { 'signature':'TEXD', 'offset':offset } )
    offset += DATA_HEADER_SIZE + TEXTURE_ST_SIZE*len(textures)
    offsets.append( { 'signature':'PLND', 'offset':offset } )
    offset += DATA_HEADER_SIZE + PLANE_ST_SIZE*len(planes)
    offsets.append( { 'signature':'SPRT', 'offset':offset } )
    offset += DATA_HEADER_SIZE + SPRITE_ST_SIZE*len(sprites)
    offsets.append( { 'signature':'9SPR', 'offset':offset } )
    offset += DATA_HEADER_SIZE + NINE_SPRITE_ST_SIZE*len(nine_sprites)
    offsets.append( { 'signature':'COMP', 'offset':offset } )
    offset += DATA_HEADER_SIZE + COMPOSITION_ST_SIZE*len(compositions)
    offsets.append( { 'signature':'LAYR', 'offset':offset } )
    offset += DATA_HEADER_SIZE + LAYER_ST_SIZE*len(layers)
    offsets.append( { 'signature':'STAT', 'offset':offset } )
    offset += DATA_HEADER_SIZE + STATE_ST_SIZE*len(states)
    offsets.append( { 'signature':'SKEY', 'offset':offset } )
    offset += DATA_HEADER_SIZE + STATE_KEYFRAME_ST_SIZE*len(state_keyframes)

    for data in offsets:
        print(data)

    file_size = offset

    # SmlHeader
    outdata = struct.pack('{0}4s2HLL'.format(ENDIAN),
                          'SMLD',
                          VERSION[0],VERSION[1],
                          SML_HEADER_SIZE,
                          file_size,
                         )

    def dataHeader(signature, structSize, count):
        return struct.pack('{0}4sLL'.format(ENDIAN),signature, structSize, count)

    # data ofset
    outdata += dataHeader('DOFS', OFFSET_ST_SIZE, len(offsets))
    for data in offsets:
        outdata += struct.pack('{0}4sL'.format(ENDIAN),
                               data['signature'],
                               data['offset']
                              )

    # texture
    outdata += dataHeader('TEXD', TEXTURE_ST_SIZE, len(textures))
    for texture in textures:
        outdata += struct.pack('{0}L32s2H'.format(ENDIAN),
                               texture['id'],
                               texture['name'],
                               toSize(texture)
                              )

    # plane
    outdata += dataHeader('PLND', PLANE_ST_SIZE, len(planes))
    for plane in planes:
        outdata += struct.pack('{0}L32s2H4B'.format(ENDIAN),
                               plane['id'],
                               plane['name'].encode('utf-8'),
                               plane['size'][0], plane['size'][1],
                               plane['color'][0], plane['color'][1], plane['color'][2], plane['color'][3]
                              )

    # sprite
    outdata += dataHeader('SPRT', SPRITE_ST_SIZE, len(sprites))
    for sprite in sprites:
        outdata += struct.pack('{0}L32s2HL4f'.format(ENDIAN),
                               sprite['id'],
                               sprite['name'].encode('utf-8'),
                               sprite['size'][0], sprite['size'][1],
                               sprite['texture_id'],
                               sprite['uv'][0], sprite['uv'][1], sprite['uv'][2], sprite['uv'][3]
                              )

    # nine slice sprite
    outdata += dataHeader('9SPR', NINE_SPRITE_ST_SIZE, len(nine_sprites))
    for sprite in nine_sprites:
        outdata += struct.pack('{0}L32s2HL4f4f'.format(ENDIAN),
                               sprite['id'],
                               sprite['name'].encode('utf-8'),
                               sprite['size'][0], sprite['size'][1],
                               sprite['texture_id'],
                               sprite['uv'][0], sprite['uv'][1], sprite['uv'][2], sprite['uv'][3],
                               sprite['inner'][0], sprite['inner'][1], sprite['inner'][2], sprite['inner'][3],
                              )

    # composition
    outdata += dataHeader('COMP', COMPOSITION_ST_SIZE, len(compositions))
    for composition in compositions:
        outdata += struct.pack('{0}L32s'.format(ENDIAN),
                               composition['id'],
                               composition['name'].encode('utf-8')
                              )

    # layer
    layer_type_tbl = ('composition', 'plane', 'sprite', 'nine_slice_sprite', 'text', 'mask')
    drawing_tbl = ('normal', 'add', 'multiply')

    outdata += dataHeader('LAYR', LAYER_ST_SIZE, len(layers))
    for layer in layers:
        outdata += struct.pack('{0}LLLL32s2f2f2ff4BL'.format(ENDIAN),
                               layer['id'],
                               layer['composition_id'],
                               layer_type_tbl.index(layer['type']),
                               layer['type_id'],
                               layer['name'].encode('utf-8'),
                               layer['anchor'][0],layer['anchor'][1],
                               layer['pos'][0],layer['pos'][1],
                               layer['scale'][0], layer['scale'][1],
                               layer['rotate'],
                               layer['color'][0],layer['color'][1],layer['color'][2],layer['color'][3],
                               drawing_tbl.index(layer['drawing_mode'])
                              )

    # state
    outdata += dataHeader('STAT', STATE_ST_SIZE, len(states))
    for state in states:
        outdata += struct.pack('{0}LL32sfL'.format(ENDIAN),
                               state['id'],
                               state['composition_id'],
                               state['name'].encode('utf-8'),
                               state['duration'],
                               state['next_state_id']
                              )

    # state keyframe
    value_type_tbl = (
        'anchor_x', 'anchor_y',
        'pos_x', 'pos_y',
        'scale_x', 'scale_y',
        'rotate',
        'color_r', 'color_g', 'color_b', 'color_a'
    )

    outdata += dataHeader('SKEY', STATE_KEYFRAME_ST_SIZE, len(state_keyframes))
    for keyframe in state_keyframes:
        outdata += struct.pack('{0}LLfL3f'.format(ENDIAN),
                              keyframe['state_id'],
                              keyframe['layer_id'],
                              keyframe['frame'],
                              value_type_tbl.index(keyframe['type']),
                              keyframe['value'],
                              keyframe['in'] if 'in' in keyframe else 0,
                              keyframe['out'] if 'out' in keyframe else 0
                             )


    f = open('test_data.sml', 'wb')
    f.write(outdata)
    f.close()


if __name__=='__main__':
    main()

