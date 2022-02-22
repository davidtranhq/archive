function initGame()
	platforms = {}
	ball = {
		x = 160,
		y = 284,
		accel = 0
	}
end

function love.load()
	initGame()
	state = "start"
end

function love.draw()
	love.graphics.setBackgroundColor(255,255,255)
	love.graphics.setColor(0,0,0)
		love.graphics.circle("line",ball.x,ball.y,15)
	for id, plat in pairs(platforms) do
		love.graphics.line(plat.x1,plat.y1,plat.x2,plat.y2)
		love.graphics.print(math.sqrt( math.abs(plat.x2-plat.x1)^2 + math.abs(plat.y1-plat.y2)^2 ))
	end
end

function love.update()
	if state == "play" then
		ball.accel = ball.accel+0.1
		ball.y = ball.y+ball.accel
	end
end

function love.touchpressed(id,x,y)
end

function love.touchmoved(id,x,y,dx,dy)
end

function love.touchreleased(id,x,y)
end

function love.mousepressed(x,y)
	--create platform
	for platform = 1, #platforms+1 do 
		if not platforms[platform] then --if no registered platform, create
			platforms[platform] = {
				x1 = x,
				y1 = y,
				x2 = x,
				y2 = y,
				isDone = false
			}
		end
	end
end

function love.mousemoved(x,y,dx,dy)
	for id, plat in pairs(platforms) do
		if not plat.isDone then
			platforms[id].x2 = x
			platforms[id].y2 = y
			if math.sqrt( math.abs(x-plat.x1)^2 + math.abs(y-plat.y1)^2 ) > 50 then --if segement is larger than 50
				local angle = math.atan( math.abs(y-plat.y1)/math.abs(x-plat.x1) )
				platforms[id].x2 = x > plat.x1 and math.cos(angle)*50 + plat.x1 or -(math.cos(angle)*50) + plat.x1
				platforms[id].y2 = y > plat.y1 and math.sin(angle)*50 + plat.y1 or -(math.sin(angle)*50) + plat.y1
			end
		end
	end
end

function love.mousereleased(x,y)
	for id, plat in pairs(platforms) do
		if not plat.isDone then
			plat.isDone = true
		end
		if state == "start" then
			state = "play"
		end
	end
end
