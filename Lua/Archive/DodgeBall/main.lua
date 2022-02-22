require "score"
function newBall(i)
	ball[i] = {}
	ball[i].size = math.random(10, 20)
	ball[i].x, ball[i].y = math.random(0+ball[i].size, window-ball[i].size), math.random(0+ball[i].size, window-ball[i].size) 
	ball[i].xstep, ball[i].ystep = math.random(0, 0), math.random(0, 0)
	kind = math.random(1,15)
	ball[i].life = score
	for k,v in pairs(special) do
		if kind == special[k][4] then
			ball[i].sort = k
			return
		else
			ball[i].sort = "ball"
		end
		if special[k][7] == true then
			ball[i][k] = false
		end
	end
end

function debugInfo()
debugX = window-40
debugY = 14
	for k, v in pairs(ball) do
		love.graphics.print(k.." "..ball[k]["sort"], 0, debugY)
		debugY = debugY+14
	end
	debugX = 14
	for k, v in pairs(player.buffs) do
		love.graphics.print(k.." "..v, debugX, debugY)
		debugY = debugY+14
	end
end

function drawBalls()
	for k, v in pairs(ball) do
		for kk,vv in pairs(special) do
			if ball[k].sort == kk then
				love.graphics.setColor(special[kk][1], special[kk][2], special[kk][3])
				break
			elseif ball[k].sort == "ball" then
				love.graphics.setColor(255, 255, 255)
				break
			end
		end
		love.graphics.circle("fill", ball[k].x, ball[k].y, ball[k].size)
	end
end

function drawBuffs()
	for k,v in pairs(player.buffs) do
		if player.buffs[k] ~= 0 then 
			love.graphics.setColor(special[k][1], special[k][2], special[k][3])
			love.graphics.circle("fill", player.x, player.y, player.size+(special[k][5]-math.abs(player.buffs[k]-score))/10)
		end
	end
end

function drawPlayer()
	love.graphics.setColor(150, 150, 150)
	love.graphics.circle("fill", player.x, player.y, player.size)
	love.graphics.print(score, 0, 0)
end

function movePlayer()
player.x, player.y = love.mouse.getX(), love.mouse.getY()
end

function checkSafe()
	for k, v in pairs(player.buffs) do
		if special[k][6]  == true then
			if v ~= 0 then
				return false
			end
		end
	end
	return true
end

function checkCollision()
	
end
	
function updateBalls()
	for k,v in pairs(ball) do
		local a = ball[k]
		a.x, a.y = a.x+a.xstep, a.y+a.ystep
		if a.x-a.size <= 0 or a.x+a.size >= window then a.xstep = -a.xstep
		elseif a.y-a.size <= 0 or a.y+a.size >= window then a.ystep = -a.ystep
		end
		if math.abs(player.x-ball[k].x) <= player.size+ball[k].size and math.abs(player.y-ball[k].y) <= player.size+ball[k].size then
			if ball[k].sort ~= "ball" then
				player.buffs[ball[k].sort] = score
				ball[k] = nil
			elseif player.buffs.destroy > 0 then
				ball[k] = nil
			elseif ball[k].sort == "ball" and math.abs(score-ball[k].life) > 30 and checkSafe() then
				game = false
			end
		end
	end
end

function updatePlayer()
	for k, v in pairs(special) do
		if math.abs(score-player.buffs[k]) > special[k][5] then
		player.buffs[k] = 0
		end
	end
end

function saveScore()
	
		love.filesystem.write("score.lua", "hi_score = "..score, string.len("hi_score = "..score))
	
end

function updateGame()
	if score%20 == 0 then
		newBall(#ball+1)
	end
	if game == true then
		score = score+1
	elseif game == false then
		saveScore()
		if love.keyboard.isDown("space") then
			love.load()
		end
	end
end

function loadBuffs()
	if player.buffs.shrink > 0 then
		for k,v in pairs(ball) do
			if ball[k].shrink == false then
				ball[k].shrink = true
				ball[k].size = ball[k].size/2
			end
		end
	elseif player.buffs.shrink == 0 then
		for k,v in pairs(ball) do
			if ball[k].shrink == true then
				ball[k].shrink = false
				ball[k].size = ball[k].size*2
			end
		end
	end
	if player.buffs.double > 0 and game == true then
		score = score+1
	end
	if player.buffs.slow > 0 then
		for k,v in pairs(ball) do
			if ball[k].slow == false then
				ball[k].slow = true
				ball[k].xstep, ball[k].ystep = ball[k].xstep/2, ball[k].ystep/2
			end
		end
	elseif player.buffs.slow == 0 then
		for k,v in pairs(ball) do
			if ball[k].slow == true then
				ball[k].slow = false
				ball[k].xstep, ball[k].ystep = ball[k].xstep*2, ball[k].ystep*2
			end
		end
	end
		
end

function love.load()
math.randomseed( os.time() ) --ensures a random seed
math.random()
math.random()
game = true
shrink = false
slow = false
score = 0
window = 650
love.window.setMode(window, window)
player = {}
ball = {}
special = {
	shield = {0, 0, 255, 15, 240, true, false}, --1-3 = RGB, 4 = RNG, 5 = time, 6 = protect, 7 = mod
	destroy = {255, 0, 0, 14, 120, true, false},
	double = {0, 255, 0, 13, 300, false, false},
	shrink = {255, 255, 0, 12, 300, false, true},
	slow = {186,85,211, 11, 300, false, true}
}
	player.x, player.y = window/2, window/2
	player.size = 20
	player.safe = false
	player.buffs = {
		double = 0,
		shrink = 0,
		slow = 0,
		shield = 0,
		destroy = 0,
	}	
	for i = 1, 5 do
		newBall(i)
	end
end

function love.draw()
	if game == true then
		drawBalls()
		drawBuffs()
		drawPlayer()
	elseif game == false then
	love.graphics.printf("Game Over! \n Score: "..score.." \n Press SPACE to restart!", 0, window/2, window, "center" )
	end
end

function love.update()
	movePlayer()
	updateBalls()
	updatePlayer()
	updateGame()
	loadBuffs()
end