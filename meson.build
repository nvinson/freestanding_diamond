project('freestanding_diamond', 'cpp',
  version : '0.1',
  default_options : ['cpp_link_args=-ffreestanding -nostdlib -nostartfiles', 'warning_level=3', 'cpp_std=c++14'])

executable('freestanding_diamond',
           'diamond.cc',
           'exit_group.s',
           'start.s',
           'write.s',
           install : true)
