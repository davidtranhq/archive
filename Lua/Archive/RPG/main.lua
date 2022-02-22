require "map-functions"
require "unit-functions"
function love.load()
loadMap("map1")
loadPlayer()
end

function love.draw()
drawMap()
drawPlayer()
end

function love.update()
movePlayer()
end