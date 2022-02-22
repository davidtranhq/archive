function sleep(n)  -- seconds
  local t0 = os.clock()
  while os.clock() - t0 <= n do end
end

function newStartText(text, x, y, font, choice)
	start_text[text] = { 
		x = x - font:getWidth(text)/2, --offset (centering)
		y = y,
		font = font,
		choice = choice
	}
	if choice then
		start_text_index[#start_text_index+1] = text 
	end
end

function newFruit()
	local x,y = 0, 0
	repeat
		x,y = math.random(1,#grid), math.random(1,#grid[1])
	until grid[x][y] == 0
	grid[x][y] = -1 --place fruit on blank square
end

function checkTile(check)
	return grid[head.x][head.y] == check
end

function saveScore()
	saved = true
	love.filesystem.append("scores.lua", "\nscores[".. #scores+1 .."] = {'"..length.."','"..name.."','"..os.date().."'}")
	loadScores = love.filesystem.load("scores.lua")
	loadScores()
end

function sortScores()
	if #scores == 1 then
		return scores
	end
	repeat
		hasChanged = false
		for index, scoredata in pairs(scores) do
			if index < #scores then
				if tonumber(scoredata[1]) < tonumber(scores[index+1][1]) then
					scores[index], scores[index+1] = scores[index+1], scoredata
					hasChanged = true
					a = a + 1
				end
			end
		end
	until hasChanged == false
end

function loadGame()
	grid = {}
	timer = 0
	length = 1
	tile_size = 30
	for x = 1, math.floor(xwindow/tile_size) do
		grid[x] = {}
		for y = 1, math.floor(ywindow/tile_size) do
			grid[x][y] = 0
		end
	end --create game board
	
	head = {x = math.random(3,#grid-3), y = math.random(3,#grid[1]-3)}	--determine snake start
	grid[head.x][head.y] = 1
	move = {0,0}
	newFruit()
end

function loadStart()
	titleFont = love.graphics.newFont("font.ttf", 72)
	gameFont = love.graphics.newFont("font.ttf", 48)
	smallFont = love.graphics.newFont("font.ttf", 36)
	start_text = {}
	start_text_index = {}
	start_select = 0
	start_choice = 1
	newStartText("snake.", xwindow/2, ywindow/5, titleFont, false)
	newStartText("play", xwindow/4, ywindow*3/5, gameFont, true)
	newStartText("about", xwindow/2, ywindow*4/5, gameFont, true)	
	newStartText("hi-scores", xwindow*3/4, ywindow*3/5, gameFont, true)
end

function updateGame()
	local l = love.keyboard.isDown --table handle, reduce characters
	if l('w') or l('up') then
		move = {0,-1}
	elseif l('a') or l('left') then
		move = {-1,0}
	elseif l('s') or l('down') then
		move = {0,1}
	elseif l('d') or l('right') then
		move = {1,0}
	end --controls
	
	if delay == 0 then
		head.x = head.x+move[1]
		head.y = head.y+move[2] 
			for x = 1, #grid do
				for y = 1, #grid[x] do
				if grid[x][y] == length then
					grid[x][y] = 0
				end
				if grid[x][y] > 0 then
					grid[x][y] = grid[x][y] + 1
				end
			end
		end --move player
	
		if grid[head.x] == nil or grid[1][head.y] == nil then --if player crash
			state = "End"
			return
		elseif grid[head.x][head.y] > 1 then 
			state = "End"
			return
		elseif checkTile(-1) then
			length = length + 1
			newFruit()
		end	
		delay = 5
		
		grid[head.x][head.y] = 1
	end
	delay = delay - 1
end

function updateTransition()
	if fade_out == true then
		fade = fade - 5
	elseif fade_out == false and fade < 255 then
		fade = fade + 5
	end
	if fade <= 0 then
		fade_out = false
		if state == "start" then
			name = "__________"
			state = start_text_index[start_choice]
			loadHighScores()
			loadGame()
		else 
			delay = 0
			state = "start"
		end
	end
end

function updateStart()
	saved = false
	if delay == 0 then
		if love.keyboard.isDown("left") then
			start_choice = start_choice - 1 
			if start_choice < 1 then
				start_choice = #start_text_index
			end
			start_select = 0
			delay = 10
		elseif love.keyboard.isDown("right") then
			start_choice = start_choice + 1
			if start_choice > #start_text_index then
				start_choice = 1
			end
			delay = 10
			start_select = 0
		end
	end
	if delay > 0 then
		delay = delay - 1
	end
	if love.keyboard.isDown("return") then
		fade_out = true
		fade = 255
	end
	if start_select < gameFont:getWidth(start_text_index[start_choice]) then
		start_select = start_select + 5
	end
end

function drawStart()
	for text, data in pairs(start_text) do
		love.graphics.setFont(data.font)
		love.graphics.print(text, data.x, data.y)
	end
	local y = start_text[start_text_index[start_choice]].y + gameFont:getHeight(start_text_index[start_choice]) + 5
	local x = start_text[start_text_index[start_choice]].x
	love.graphics.line(x, y, x+start_select, y)
end

function drawGame()
	for x = 1, #grid do
		for y,data in pairs(grid[x]) do
			if grid[x] and grid[y] then
				if data == -1 then
					love.graphics.rectangle("fill", (x*tile_size-tile_size) + tile_size*0.25, (y*tile_size-tile_size) + tile_size*0.25, tile_size*0.5, tile_size*0.5) 
				elseif data > 0 then
					love.graphics.rectangle("line", (x*tile_size-tile_size) + tile_size*0.125, (y*tile_size-tile_size) + tile_size*0.125, tile_size*0.75, tile_size*0.75)
				end
			end
		end
	end
end

function drawEnd()
	love.graphics.setFont(titleFont)
	love.graphics.rectangle("line", xwindow/5, ywindow/4, xwindow*3/5, ywindow*2/4)
	love.graphics.printf("game over", xwindow/5, ywindow/3, xwindow*3/5, "center")
	love.graphics.setFont(smallFont)
	love.graphics.printf("score: "..length, xwindow/5+5, ywindow*3/5, xwindow*3/5, "left")
	love.graphics.printf("name: "..name, xwindow/5+5, ywindow*2/3, xwindow*3/5, "left")
end

function updateEnd()
	for id, letter in pairs(alpha) do
		if love.keyboard.isDown(letter) and delay <= 0 then
			name = name:gsub("_", letter, 1)
			delay = 10
			break
		elseif love.keyboard.isDown("backspace") and delay <= 0 then
			backspace_name = name:reverse()
			name = backspace_name:gsub("[^_]", "_", 1):reverse()
			delay = 10
		end
	end
	if love.keyboard.isDown("return") and saved == false then
		if name ~= "__________" then
			name = name:gsub("[_]", "")
			saveScore()
		end
		fade_out = true
	end
	delay = delay-1
end

function loadHighScores()
	sortScores()
end

function drawHighScores()
	love.graphics.setFont(titleFont)
	love.graphics.printf("hi-scores", 0,ywindow/10,xwindow,'center')
	love.graphics.setFont(gameFont)
	for index,scoredata in ipairs(scores) do
		if index <= scroll and index > scroll - 8 then
			local y = ywindow/4 + gameFont:getHeight()*(index+8-scroll)
			love.graphics.print(index..".",10, y)
			love.graphics.print(scoredata[2], xwindow/10, y)
			love.graphics.print(scoredata[1], xwindow*7/16, y)
			love.graphics.print(scoredata[3], xwindow*9/16, y)
		end
	end
end

function updateHighScores()
	if love.keyboard.isDown("return") then
		fade_out = true
	elseif love.keyboard.isDown("up") and scroll > 8 and delay <= 0 then
		scroll = scroll - 1
		delay = 5
	elseif love.keyboard.isDown("down") and scroll < #scores and delay <= 0 then
		scroll = scroll + 1
		delay = 5
	end
	delay = delay - 1
end

function updateAbout()
	if love.keyboard.isDown('return') then
		fade_out = true
	end
end

function drawAbout()
	love.graphics.printf("Created by David Tran \nCompleted 2:44PM 2016-07-07 \nVersion 2.1", 10, 10, xwindow-10, "left")
end

function love.load()
	math.randomseed( os.clock() )
	math.random(); math.random()
	if not love.filesystem.exists("scores.lua") then
		scores = love.filesystem.newFile("scores.lua")
		love.filesystem.append("scores.lua", "scores = {}")
	end
	a = 0
	start_choice = 1
	scroll = 8
	xwindow, ywindow = love.window.getMode()
	loadScores = love.filesystem.load("scores.lua")
	loadScores()
	delay = 0
	defaultFont = love.graphics.getFont()
	love.graphics.setBackgroundColor(255,255,255)
	alpha = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0',"'",'.'}
	name = "__________"
	state = "start"
	fade = 255
	loadStart()
	loadGame()
end

function love.draw()
	love.graphics.setColor(0,0,0,fade)
	if state == "start" then
		drawStart()
	elseif state == "play" then
		drawGame()
	elseif state == "hi-scores" then
		drawHighScores()	
	elseif state == "about" then
		drawAbout()
	elseif state == "End" then
		drawGame()
		drawEnd()
	end
end

function love.update()
	if state == "start" then
		updateStart()
	elseif state == "play" then	
		updateGame()
	elseif state == "End" then
		updateEnd()
	elseif state == "hi-scores" then
		updateHighScores()
	elseif state == "about" then
		updateAbout()
	end
	updateTransition()
end