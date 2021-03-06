#!/usr/bin/env python
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import os
import sys
import setuptools

__version__ = '0.0.1'

PYTHON_ROOT_DIR = os.path.dirname(os.path.abspath(__file__))

class get_pybind_include(object):
    """Helper class to determine the pybind11 include path
    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)


ext_modules = [
    Extension(
        'kkkvspy',
        [os.path.join(PYTHON_ROOT_DIR, 'src', 'kkkvspy.cpp')],
        include_dirs=[
            # Path to pybind11 headers
            get_pybind_include(),
            get_pybind_include(user=True),
            os.path.join(PYTHON_ROOT_DIR, '..', 'include')
        ],
        extra_objects=['../lib/kkkvs/libkkkvs.a'] if sys.platform != 'win32' else ['../lib/kkkvs/Release/kkkvs.lib'],
        language='c++'
    ),
]


# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True


def cpp_flag(compiler):
    """Return the -std=c++[11/14] compiler flag.
    The c++14 is prefered over c++11 (when it is available).
    """
    if has_flag(compiler, '-std=c++14'):
        return '-std=c++14'
    elif has_flag(compiler, '-std=c++11'):
        return '-std=c++11'
    else:
        raise RuntimeError('Unsupported compiler -- at least C++11 support '
                           'is needed!')


class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    c_opts = {
        'msvc': ['/EHsc'],
        'unix': [],
    }

    if sys.platform == 'darwin':
        c_opts['unix'] += ['-stdlib=libc++', '-mmacosx-version-min=10.7']

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])
        if ct == 'unix':
            opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
            opts.append(cpp_flag(self.compiler))
            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
        elif ct == 'msvc':
            opts.append('/DVERSION_INFO=\\"%s\\"' % self.distribution.get_version())
        for ext in self.extensions:
            ext.extra_compile_args = opts
        build_ext.build_extensions(self)

setup(name = 'kkkvs',
      author = 'ksgwr',
      author_email = 'ksgwarai@gmail.com',
      description = 'KKKVS python wrapper',
      long_description = 'KKKVS python wrapper',
      version='0.0.2',
      url = 'https://github.com/ksgwr/KKKVS',
      license = 'Apache',
      platforms = 'Unix',
      setup_requires = ['pytest-runner'],
      tests_require = ['pytest'],
      ext_modules=ext_modules,
      cmdclass={'build_ext': BuildExt},
      zip_safe=False
)
