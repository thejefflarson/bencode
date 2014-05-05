#!/usr/bin/env python


def options(opt):
    opt.load('compiler_c')


def configure(conf):
    conf.load('compiler_c')
    conf.env.append_unique('CFLAGS', ['-std=c99', '-Wall', '-Wextra', '-Werror', '-g'])
    conf.env.append_value('INCLUDES', ['include'])


def build(bld):
    sources = bld.path.ant_glob(['src/*.c'])

    bld.shlib(
        features='c cshlib',
        source=sources,
        includes=['src', 'includes'],
        target='bencode'
    )

    bld.stlib(
        features='c cstlib',
        source=sources,
        includes=['src', 'includes'],
        target='bencode'
    )

    bld.program(
        features='c',
        source='test/test_bencode.c',
        includes=['src', 'includes'],
        use='bencode',
        target='test_bencode.tap',
        install_path=None
    )
