#!/usr/bin/env python


def options(opt):
    opt.load('compiler_c')
    opt.load('bison')
    opt.load('flex')


def configure(conf):
    conf.load('compiler_c')
    conf.load('bison')
    conf.load('flex')

    conf.env.append_unique('CFLAGS', ['-std=c99', '-Wall', '-Werror', '-g'])
    conf.env.append_value('INCLUDES', ['include'])


def build(bld):
    sources = bld.path.ant_glob(['src/*.c', 'src/*.y', 'src/*.l'])

    bld.shlib(
        features='c cshlib',
        source=sources,
        includes=['src', 'include'],
        target='bencode'
    )

    bld.stlib(
        features='c cstlib',
        source=sources,
        includes=['src', 'include'],
        target='bencode'
    )

    bld.program(
        features='c',
        source='test/test_bencode.c',
        includes=['src', 'include'],
        use='bencode',
        target='test_bencode.tap',
        install_path=None
    )
