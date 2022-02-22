function love.load()
--head_img, body_img, tail_img = love.graphics.newImage("head.png"),love.graphics.newImage("body.png"),love.graphics.newImage("tail.png") 
snake = {
	length = 1,
	xgrid = 1,
	ygrid = 1,
	tile = 2,
	pos = { [1]={2, 2},},
	head = head_img,
	body = body_img,
	tail = tail_img,
	scale = 2
}
game = true
activeSnake = {}
willMove = 1
row = 20
step = 1
delay = 0
ctrls = {"up", "right", "down", "left"}
move = {0-row-1, 1, row+1, -1}
direction = 2
window = row*32
love.window.setMode(window, window)
grid = {}
local x, y = 0, 0
for i = 1, (row+1)*(row+1) do
grid[i] = {}
grid[i].x, grid[i].y = x, y
x = x+32
activeSnake[i] = false
	if i%(row+1) == 0 then
	x = 0
	y = y+32
	grid[i] = nil
	end
end
repeat fruit = math.random(2, #grid) until fruit%(row+1) ~= 0
end

function love.draw()
if game == true then
for i = 4, #snake.pos do
	if activeSnake[i] then
	--love.graphics.draw(snake.body, grid[snake.pos[i][1]].x, grid[snake.pos[i][1]].y, (snake.pos[i][2]-1)*math.pi/2, 2,2, 32,32)
	love.graphics.rectangle("fill", grid[snake.pos[i][1]].x, grid[snake.pos[i][1]].y, 32, 32)
	end
	love.graphics.rectangle("fill", grid[snake.tile].x, grid[snake.tile].y, 32, 32)
--love.graphics.draw(snake.head, grid[snake.tile].x, grid[snake.tile].y, (direction-1)*math.pi/2, 2,2, 32,32)
--love.graphics.draw(snake.tail, grid[snake.pos[#snake.pos-snake.length+1][1]].x, grid[snake.pos[#snake.pos-snake.length+1][1]].y, (snake.pos[#snake.pos-snake.length+1][2]-1)*math.pi/2, 2,2, 32,32)
end
love.graphics.rectangle("fill", grid[fruit].x, grid[fruit].y, 32, 32)
love.graphics.print(snake.length, 0, 0)
elseif game == false then
if snake.length == 42 then secret = "At least now you know The Answer..."
elseif snake.length == 77 then secret = "Can't have any better luck than that!"
elseif snake.length == 400 then secret = "Amazing! Perfect score!"
else secret = "Better luck next time!"
end
love.graphics.printf("Game Over! \n Score: "..snake.length.." \n Press SPACE to restart! \n"..secret, 0, window/2, window, "center" )
end

function checkCollision()
for p, v in pairs(activeSnake) do 
	if v == true then 
		if snake.tile == snake.pos[p][1] then 
		return true 
		end 
	end 
end
end

function love.update()
	for k, key in pairs(ctrls) do
		if love.keyboard.isDown(key) then
		direction = k
		elseif love.keyboard.isDown(" ") then
		love.load()
		end
	end
if willMove <= 0 then
	snake.tile = snake.tile+move[direction]
	snake.pos[step] = {}
	snake.pos[step][1], snake.pos[step][2] = snake.tile, direction
	for i = 1, #snake.pos do
		if i > #snake.pos-snake.length and i < #snake.pos then
		activeSnake[i] = true
		else
		activeSnake[i] = false
		end
	end
	if snake.tile == fruit then 
		snake.length = snake.length+1
		repeat fruit = math.random(1, #grid) until activeSnake[fruit] == false and fruit%(row+1) ~= 0 and fruit < row*row+1
	end
	if grid[snake.tile] == nil or checkCollision() then
	game = false
	end
	step = step+1
	willMove = 1
elseif willMove > 0 then
willMove = willMove - 0.2
end
end
end