function love.load()
math.randomseed(os.time())
math.random()
math.random()
score = 0
window = 600
ballsize = 10
ballnum = 100
popsize = 20
love.window.setMode(window, window)
balls = {}
ballpop = {}
	for i = 1, ballnum+1 do
	balls[i] = {}
	balls[i]["x"], balls[i]["y"] = math.random(0+ballsize,window-ballsize), math.random(0+ballsize,window-ballsize)
	balls[i].xstep, balls[i].ystep = math.random(-5, 5), math.random(-5, 5)
	balls[i].pop = false
	balls[i].colour = {}
		for ii = 1, 3 do
		balls[i].colour[ii] = math.random(0, 255)
		end
	end
end

function newDebug(message)
love.graphics.print(message, xdebug, ydebug)
xdebug, ydebug = xdebug+14, ydebug+14
end

function debugInfo()
xdebug, ydebug = 0, 0
love.graphics.setFont( love.graphics.newFont(14))
newDebug("FPS="..love.timer.getFPS() )
end

function love.draw()
	for k, v in pairs(balls) do
		if balls[k].pop == false then
			love.graphics.setColor(balls[k].colour[1], balls[k].colour[2], balls[k].colour[3])
			love.graphics.circle("fill", balls[k]["x"], balls[k]["y"], ballsize)
		end
		for k, v in pairs(ballpop) do
			if ballpop[k].timer <= 0 then
			else
				if k == ballnum+1 then
					love.graphics.setColor(255, 255, 255)
				else
					love.graphics.setColor(balls[k].colour[1], balls[k].colour[2], balls[k].colour[3])
				end
				love.graphics.circle("fill", ballpop[k].x, ballpop[k].y, popsize)
			end
		end
	end
	love.graphics.print(score, 0,0)
	--debugInfo()
end

function love.update()
	for k, v in pairs(balls) do
		if balls[k].pop == false then
		balls[k]["x"], balls[k]["y"] = balls[k]["x"]+balls[k].xstep, balls[k]["y"]+balls[k].ystep
			if balls[k]["x"] <= 0 or balls[k]["x"] >= window then balls[k].xstep = -balls[k].xstep
			elseif balls[k]["y"] <= 0 or balls[k]["y"] >= window then balls[k].ystep = -balls[k].ystep
			end
			for kk, vv in pairs(ballpop) do
				if ballpop[kk].timer <= 0 then
				else
					if math.abs(balls[k].x-ballpop[kk].x) < ballsize+popsize and math.abs(balls[k].y-ballpop[kk].y) < ballsize+popsize then
					ballpop[k] = {}
					ballpop[k].x, ballpop[k].y = balls[k].x, balls[k].y
					ballpop[k].timer = 10
					score = score+10
					balls[k].pop = true
					end
				end
			end
		else
		end
	end
	for k,v in pairs(ballpop) do 
		if ballpop[k].timer <= 0 then
		else
		ballpop[k].timer = ballpop[k].timer-0.1
		end
	end
	if love.keyboard.isDown("space") then
		ballpop[ballnum+1] = {}
		ballpop[ballnum+1].x, ballpop[ballnum+1].y = love.mouse.getX(), love.mouse.getY()
		ballpop[ballnum+1].timer = 10
	elseif love.keyboard.isDown("s") then
	love.load()
	end
end