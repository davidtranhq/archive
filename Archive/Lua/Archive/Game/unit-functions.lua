function loadPlayer()
love.filesystem.load("playerdata.lua")()
selectNum = 1
selectedPlayer = captain
selected_image = love.graphics.newImage("/images/selected.png")
selectionDelay = 1
activePlayers = {captain, soldier}
playerSprite = {}
for k, player in ipairs(activePlayers) do
playerSprite[k] = love.graphics.newImage(player.img)
player.canMove = 0
player.inipos = player.tile
end
end

function loadEnemy(enemy)
activeEnemies = {}
enemySprite = {}
local i = 1
for enemy, lvl in pairs(enemy) do
activeEnemies[i] = enemmy
enemySprite[i] = love.graphics.newImage(enemy.img)
i = i+1
end
end

function drawEnemies()
for k, e in pairs(activeEnemies) do
love.graphics.draw(enemySprite[k])
end
end

function selectPlayer()
if (love.keyboard.isDown("left") or love.keyboard.isDown("right")) and selectionDelay <= 0 then
	if love.keyboard.isDown("left") and selectionDelay <= 0 then
	var1, var2, var3 = selectNum-1, #activePlayers, 1
	elseif love.keyboard.isDown("right") and selectionDelay <= 0 then
	var1, var2, var3 = selectNum+1, 1, #activePlayers
	end
	selectedPlayer.inipos = selectedPlayer.tile
	selectedPlayer = activePlayers[var1] or activePlayers[var2]
	selectionDelay = 1
	if selectNum == var3 then selectNum = var2
	else selectNum = var1
	end
end
	selectionDelay = selectionDelay - 0.05
end

function checkRange(a)
local p = selectedPlayer
for ii = -p.range, p.range do
	for i = -p.range, p.range do
	if p.inipos%tilerow+i < 0 then i = i+p.inipos%tilerow end
	local tilecheck = (p.inipos+i)+tilerow*ii or 1 --finally! the formula
	love.graphics.draw(selected_image, tileTable[1].x, tileTable[1].y)
	if a == tilecheck then
	return true
	end
	end
end
startpoint = nil
end

function movePlayer()
	for k, key in ipairs(selectedPlayer.ctrlkey) do
	local sP = selectedPlayer
		if love.keyboard.isDown(key) and sP.canMove <= 0 and tileTable[sP.tile+sP.ctrls[k]]["type"] == "ground" and checkRange(sP.tile+sP.ctrls[k]) then
		sP.tile = sP.tile+sP.ctrls[k]
		sP.canMove = 1
		end
	sP.canMove = sP.canMove - 0.05
	end
end

function endTurn()
if love.keyboard.isDown("e") then
for k, player in pairs(activePlayers) do
player.inipos = player.tile
comTurn = true
end
end
end
	
function drawPlayer()
for k, p in pairs(activePlayers) do
	love.graphics.draw(playerSprite[k], tileTable[p.tile].x, tileTable[p.tile].y)
	if p == selectedPlayer then
	love.graphics.draw(selected_image, tileTable[p.tile].x, tileTable[p.tile].y)
	end
end
end