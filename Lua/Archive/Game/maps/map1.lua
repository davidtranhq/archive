quadinfo = {
	{" ", 0, 0, "ground"},
	{"#", 32, 0, "wall"},
	{"w", 0, 32, "water"},
	{"^", 32, 32, "ground"}
}

tileString = [[
############
#          #
#          #
#          #
#          #
#          #
#          #
#          #
#          #
#          #
#          #
############
]]

newMap(32, 32, "/images/map1.png", tileString, quadinfo)