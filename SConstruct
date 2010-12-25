env = Environment(CXXFLAGS = "-O2 -Wall -Wextra -Werror -std=c++0x -pedantic")

destdir = ARGUMENTS.get("destdir", "")

crowrt = env.Library("fsroot/lib/crowrt", Glob("src/crowrt/*.c"))
crowrt_headers = env.Install("fsroot/include/crow", Glob("src/crowrt/*.h"))
crowc = env.Program("fsroot/bin/crowc", Glob("src/crowc/*.cc"))
crowl = env.Install("fsroot/bin", "src/crowl/crowl")

bin = env.Install(destdir + "/usr/bin", Glob("fsroot/bin/*"))
lib = env.Install(destdir + "/usr/lib", Glob("fsroot/lib/*"))
include_crow = env.Install(destdir + "/usr/include/crow", Glob("fsroot/include/crow/*"))
env.Alias("install", [bin, lib, include_crow])

Default(crowrt, crowrt_headers, crowc, crowl)

