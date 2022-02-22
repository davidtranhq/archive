function loadPlayer()
love.filesystem.load("playerdata.lua")()
playerSprite = love.graphics.newImage(player.img)
player.canMove = 0
end


function movePlayer()
	for k, key in ipairs(player.ctrlkey) do
	local sP = player
		if love.keyboard.isDown(key) and sP.canMove <= 0 and tileTable[sP.tile+sP.ctrls[k]]["type"] == "ground" then
		sP.tile = sP.tile+sP.ctrls[k]
		sP.canMove = 1
		end
	sP.canMove = sP.canMove - 0.025
	end
end

function drawPlayer()
	love.graphics.draw(playerSprite, tileTable[player.tile].x, tileTable[player.tile].y)
end