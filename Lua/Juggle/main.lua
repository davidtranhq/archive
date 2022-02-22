function love.load()

	new_ball = function()
		for id = 1, #ball+1 do
			if ball[id] == nil then
				ball[id] = {
					coord = {x=math.random(ball_size*2,display_width-ball_size*2),y=math.random(0,display_height/2)},
					velocity = {x=0,y=0}
				}
				break
			end
		end
	end
	
	if not love.filesystem.exists("score.lua") then
		love.filesystem.newFile("score.lua")
		love.filesystem.write("score.lua", "high_score = 0")
	end
	math.random();math.random();math.random()
	love.filesystem.load("score.lua")()
	point_sound = love.audio.newSource("audio/point.ogg", "static")
	wall_sound = love.audio.newSource("audio/wall.ogg", "static")
	score = 0
	fade = 255
	transition = false
	fade_direction = false
	display_width, display_height = 320,568
	wall_width = display_width/20
	ball_size = display_width/10
	center_size = display_width/4
	love.window.setMode(display_width,display_height)
	state = "start"
	title_font = love.graphics.newFont("font.ttf", display_width/6)
	text_font = love.graphics.newFont("font2.ttf", display_width/14)
	score_font = love.graphics.newFont("font2.ttf",center_size)
	end_font = love.graphics.newFont("font2.ttf",display_width/8)
	ball = {}
	ball[1] = {
		coord = {x=display_width/2, y=display_height/2},
		velocity = {x=0,y=0}
	} --create first ball
	
end

function love.draw()
	
	love.graphics.setBackgroundColor(240,240,240)
	love.graphics.setColor(200,200,200)
	love.graphics.rectangle("fill",0,0,wall_width,display_height) --draw right wall
	love.graphics.rectangle("fill",display_width-wall_width,0,wall_width,display_height) --draw left wall
	love.graphics.rectangle("fill",0,0,display_width,wall_width) --top wall
	love.graphics.setColor(220,220,220)
	love.graphics.circle("fill",display_width/2,display_height/2,center_size) --draw score circle
	love.graphics.setColor(240,240,240)
	love.graphics.circle("fill",display_width/2,display_height/2,center_size-10) --draw score circle
	love.graphics.setColor(200,200,200)
	love.graphics.setFont(score_font)
	love.graphics.printf(score, display_width/2-center_size, display_height/2-score_font:getHeight(score)/2, center_size*2, "center") --print score
	love.graphics.setColor(0,206,209)
	for id,info in pairs(ball) do
		love.graphics.circle("fill", info.coord.x, info.coord.y, ball_size)
	end --draw balls
	
	if state == "start" or state == "game" then
		love.graphics.setColor(210,210,210,fade)
		love.graphics.setFont(title_font)
		love.graphics.printf("Juggle", display_width/4, display_height/6, display_width/2, "center")
		love.graphics.setFont(text_font)
		love.graphics.printf("High score: "..tostring(high_score).."\nTap to throw", display_width/4, display_height*3/4, display_width/2, "center")
	end
	
	if state == "lose" then
		love.graphics.setColor(0,206,209,fade)
		love.graphics.rectangle("fill", display_width/8, display_height/3, display_width*3/4, display_height/5, 10, 10)
		love.graphics.rectangle("fill", display_width/8, display_height*11/20, display_width*3/4, display_height/10, 10,10)
		love.graphics.setColor(255,255,255,fade)
		love.graphics.setFont(end_font)
		love.graphics.printf(score.."\njuggles",display_width/8,display_height/3+10, display_width*3/4, "center")
		love.graphics.printf("REPLAY", display_width/8, display_height*11/20+10, display_width*3/4,"center")
	end
end

function love.update()

	if state == "game" then
	
		for id,info in pairs(ball) do
		
			info.velocity.y = info.velocity.y+0.1+score/1000 --ball gravity
			info.coord.x, info.coord.y = info.coord.x + info.velocity.x, info.coord.y + info.velocity.y --move ball
			if info.coord.x-ball_size <= wall_width or info.coord.x+ball_size >= display_width-wall_width then wall_sound:play(); info.velocity.x = -info.velocity.x end
			if info.coord.y-ball_size <= wall_width then info.velocity.y = 1; wall_sound:play() end
			if info.coord.y-ball_size >= display_height then 
				transition= "lose"
				fade_direction = false
				if score > high_score then
					love.filesystem.write("score.lua", "high_score = "..score)
				end
				love.filesystem.load("score.lua")()
			end
			
		end
		
	end
	
	if transition then
		if fade_direction then	
			state = transition
			fade = fade - 10
			if fade <= 0 then
				transition = false
			end
		else
			state = transition
			fade = fade+10
			if fade >= 255 then
				transition = false
			end
		end
	end
	
end

function love.touchpressed(id,x,y)
	
	for id,info in pairs(ball) do
		
		if  x >= info.coord.x-ball_size
		and x <= info.coord.x+ball_size
		and y >= info.coord.y-ball_size
		and y <= info.coord.y+ball_size and state == "game" then --if ball clicked
			point_sound:play()
			info.velocity.x = math.random(-5,5)
			info.velocity.y = -10-score/100
			score = score + 1
			if score%(#ball*10) == 0 and #ball > 1 then
				new_ball()
			elseif score == 5 then
				new_ball()
			end
		end
	end
	
	if state == "start" then transition = "game"; fade_direction = true end --start game
	
	if x >= display_width/8
	and x <= display_width*7/8
	and y >= display_height*11/20
	and y <= display_height*13/20 
	and state == "lose" then --replay button
		transition = "start"
		fade_direction = false
		score = 0
		ball = {}
		ball[1] = {
		coord = {x=display_width/2, y=display_height/2},
		velocity = {x=0,y=0}
	} --create first ball
	end
		
end

function love.mousepressed(x,y)
	love.touchpressed(id,x,y)
end
