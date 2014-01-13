import os
import ycm_core
from clang_helpers import PrepareClangFlags

# Set this to the absolute path to the folder (NOT the file!) containing the
# compilation_database.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.
compilation_database_folder = ''

# These are the compilation flags that will be used in case there's no
# compilation database set or for header files with no corresponding *.c file
# WARNING: this is truly 'last resort' solution, might not be perfect
flags = [
'-std=c++11',
'-Wall',
'-Wextra',
'-Wshadow',
'-Wno-unused-parameter',
'-Wno-parentheses',
'-pedantic',
'-g',
'-O0',
'-DUSE_CLANG_COMPLETER',
'-x',
'c++',
'-isystem',
'./',
'-isystem',
'/home/miszak/build/libclang-tools/clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu/include'
]


if compilation_database_folder:
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None


def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )


def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return flags
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def FindFile(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)


def FlagsForFile( filename ):
  if database:
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    basename = os.path.basename(filename)
    fname, ext = os.path.splitext(basename)
    orig_fname = filename
    compilation_info = None
    override = False
    if ext == ".h":
        filename = fname + ".c"
        filename = FindFile(filename, DirectoryOfThisScript())
    if filename == None and ext == '.h':
        filename = fname + ".cpp"
        filename = FindFile(filename, DirectoryOfThisScript())
    if filename != None:
        compilation_info = database.GetCompilationInfoForFile( filename )
        override = len(compilation_info.compiler_flags_) == 0

    global flags
    flags.append(orig_fname)
    final_flags = MakeRelativePathsInFlagsAbsolute(flags, DirectoryOfThisScript()) \
        if override or compilation_info == None else \
        MakeRelativePathsInFlagsAbsolute(compilation_info.compiler_flags_,
                                         compilation_info.compiler_working_dir_)

  else:
    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {
    'flags': final_flags,
    'do_cache': True
  }
