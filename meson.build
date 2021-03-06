project('pkgconf', 'c',
  version : '1.4.0',
  license : 'ISC',
  meson_version : '>=0.40')


cc = meson.get_compiler('c')


cdata = configuration_data()
check_headers = [
  ['HAVE_DLFCN_H', 'dlfcn.h'],
  ['HAVE_INTTYPES_H', 'inttypes.h'],
  ['HAVE_MEMORY_H', 'memory.h'],
  ['HAVE_STDINT_H', 'stdint.h'],
  ['HAVE_STDLIB_H', 'stdlib.h'],
  ['HAVE_STRINGS_H', 'strings.h'],
  ['HAVE_STRING_H', 'string.h'],
  ['HAVE_SYS_STAT_H', 'sys/stat.h'],
  ['HAVE_SYS_TYPES_H', 'sys/types.h'],
  ['HAVE_UNISTD_H', 'unistd.h'],
]

foreach h : check_headers
  if cc.has_header(h.get(1))
    cdata.set(h.get(0), 1)
  endif
endforeach

check_functions = [
  ['HAVE_CYGWIN_CONV_PATH', 'cygwin_conv_path', '#include<sys/cygwin.h>'],
  ['HAVE_STRLCAT', 'strlcat', '#include<string.h>'],
  ['HAVE_STRLCPY', 'strlcpy', '#include<string.h>'],
  ['HAVE_STRNDUP', 'strndup', '#include<string.h>'],
]

foreach f : check_functions
  if cc.has_function(f.get(1), prefix : f.get(2))
    cdata.set(f.get(0), 1)
  endif
endforeach

default_path = []
foreach f : ['libdir', 'datadir']
  default_path += [join_paths(get_option('prefix'), get_option(f), 'pkgconfig')]
endforeach

cdata.set_quoted('SYSTEM_LIBDIR', join_paths(get_option('prefix'), get_option('libdir')))
cdata.set_quoted('SYSTEM_INCLUDEDIR', join_paths(get_option('prefix'), get_option('includedir')))
cdata.set_quoted('PKG_DEFAULT_PATH', ':'.join(default_path))
cdata.set_quoted('PACKAGE_NAME', meson.project_name())
cdata.set_quoted('PACKAGE_VERSION', meson.project_version())
cdata.set_quoted('PACKAGE_BUGREPORT', 'http://github.com/pkgconf/pkgconf/issues')
cdata.set('abs_top_srcdir', meson.source_root())
cdata.set('abs_top_builddir', meson.build_root())


subdir('libpkgconf')

libpkgconf = shared_library('pkgconf',
  'libpkgconf/argvsplit.c',
  'libpkgconf/audit.c',
  'libpkgconf/bsdstubs.c',
  'libpkgconf/cache.c',
  'libpkgconf/client.c',
  'libpkgconf/dependency.c',
  'libpkgconf/fileio.c',
  'libpkgconf/fragment.c',
  'libpkgconf/path.c',
  'libpkgconf/pkg.c',
  'libpkgconf/queue.c',
  'libpkgconf/tuple.c',
  install : true,
  version : '2.0.0',
  soversion : '2',
)


pkgconf_exe = executable('pkgconf',
  'main.c',
  'getopt_long.c',
  link_with : libpkgconf,
  install : true)


kyua_exe = find_program('kyua')
test('kyua', kyua_exe, args : ['--config=none', 'test', '--kyuafile=' + join_paths(meson.build_root(), 'Kyuafile'), '--build-root=' + meson.build_root()])


configure_file(input : 'Kyuafile.in', output : 'Kyuafile', configuration : cdata)
subdir('tests')


install_man('pkgconf.1')
install_data('pkg.m4', install_dir: 'share/aclocal')
