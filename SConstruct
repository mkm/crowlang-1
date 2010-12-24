

env = Environment(CCFLAGS = "-O2 -Wall -Wextra -Werror -std=c++0x -pedantic")

env.Program("fsroot/bin/crowc", Glob("src/crowc/*.cc"))
env.Install("fsroot/bin", "src/crowl/crowl")

