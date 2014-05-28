#!/usr/bin/env python


def options(opt):
    opt.load('compiler_c')
    opt.load('bison')


def configure(conf):
    conf.load('compiler_c')
    conf.load('bison')
    conf.env.append_unique('CFLAGS', ['-std=c99', '-Wall', '-Wextra', '-Werror', '-g'])
    conf.env.append_value('INCLUDES', ['include', 'src'])


def build(bld):
    sources = bld.path.ant_glob(['src/bencode.c', 'src/scanner.c', 'src/parser.y'])

    bld.shlib(
        features='c cshlib',
        source=sources,
        target='bencode'
    )

    bld.stlib(
        features='c cstlib',
        source=sources,
        target='bencode'
    )

    bld.program(
        features='c',
        source='test/test_bencode.c',
        use='bencode',
        target='test_bencode',
        install_path=None
    )
