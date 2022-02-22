function game_config()
	game_state = "menu"
end

function game_transition(state)
end

function love.load()
	screen_width, screen_height = 320,568
	love.window.setMode(screen_width,screen_height)
	titleFont = love.graphics.newFont("neistil.TTF",64)
	game_config()
end

function love.draw()
	love.graphics.setBackgroundColor(255,255,255)
	if game_state == "start" then
		love.graphics.setFont(titleFont)
		love.graphics.setColor(0,0,0)
		love.graphics.printf("Topple",0,screen_height/3,screen_width,"center")
	end
end

function love.update()
end

function love.mousepressed(x,y)
	
	if game_state == "menu" then
		game_transition("game")
	end
	
end