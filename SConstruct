

env = Environment(CXXFLAGS = "-O2 -Wall -Wextra -Werror -std=c++0x -pedantic")

env.Library("fsroot/lib/crowrt", Glob("src/crowrt/*.c"))
env.Program("fsroot/bin/crowc", Glob("src/crowc/*.cc"))
env.Install("fsroot/bin", "src/crowl/crowl")

