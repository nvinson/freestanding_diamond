project('freestanding_diamond', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++23'])

executable('freestanding_diamond',
           'freestanding_diamond.cc',
           'exit_group.s',
           'start.s',
           'write.s',
           link_args: ['-ffreestanding', '-nostdlib', '-nostartfiles'],
           install : true)

executable('diamond',
           'diamond.cc',
           build_by_default: true,
           install : true)
