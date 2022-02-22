require "map-functions"
require "unit-functions"
require "leveldata"
function playLevel(level)
function love.load()
comTurn = false
loadMap(level.map)
loadPlayer()
loadEnemy(level.enemy)
end

function love.draw()
drawMap()
drawPlayer()
drawEnemies()
end

function love.update()
if comTurn == false then
selectPlayer()
movePlayer()
endTurn()
elseif comTurn == true then
end
end
end