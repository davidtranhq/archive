function loadMap(path)
love.filesystem.load("/maps/"..path..".lua")()
end

function newMap(x, y, TileSet, tileString, quadInfo)
xquad = x
yquad = y
Tileset = love.graphics.newImage(TileSet)
xorigin, yorigin = 0, 0
TilesetX, TilesetY = Tileset:getWidth(), Tileset:getHeight()
Quads = {}
for i, info in ipairs(quadinfo) do
Quads[quadinfo[i][1]] = love.graphics.newQuad(info[2], info[3], xquad, yquad, TilesetX, TilesetY)
end
tilerow = (tileString:find("\n")-1)
tilecolumn = #tileString/tilerow-1
love.window.setMode(tilerow*xquad, tilerow*yquad)
x, y = xorigin, yorigin
tilenum = 1
tileTable = {}
	for tile in tileString:gmatch(".") do
		for k, v in pairs(quadinfo) do
			if tile == quadinfo[k][1] then
				tileTable[#tileTable+1] = {["quad"]=Quads[tile], ["x"]=x, ["y"]=y, ["num"]=tilenum, ["type"]=quadinfo[k][4]}
				x = x+xquad
			elseif tile == "\n" then 
			y = y+yquad
			x = xorigin
			tilenum = tilenum - 1
			break
			end
		end
		tilenum = tilenum + 1
	end
end

function drawMap()
for i = 1, #tileTable do
	love.graphics.draw(Tileset, tileTable[i]["quad"], tileTable[i]["x"], tileTable[i]["y"])
end
end
