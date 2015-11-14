require 'mkmf'

$libs+= " -lntk"
extension_name = 'ntk'
dir_config(extension_name)
create_makefile(extension_name)
