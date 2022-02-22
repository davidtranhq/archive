function love.load()
	delay = 0
	grid = 161
	move = {-grid, 1, grid, -1}
	control = {
		{"w", "up"},
		{"d", "right"},
		{"s", "down"},
		{"a", "left"}
	}
	tile = {}
	win = 0
	delay = 0 
	window = 600
	tilesize = window/(grid-1)
	love.window.setMode(window, window)
	for i = 1, grid*grid do
		tile[i] = {}
		if math.random(1,100) == -1 then tile[i].on = math.random(1,2) else tile[i].on = 0 end
		if i%grid == 1 then
			tile[i].x = 0
		else
			tile[i].x = ((i-1)%grid)*tilesize
		end
		tile[i].y = math.floor((i-1)/grid)*tilesize
		if i%grid == 0 then
			tile[i] = nil
		end
	end
	p2 = {
		pos = math.floor((grid-1)/2*(grid-1)+(grid-1)/3),
		dir = 4 --north, east, south, weast
	}
	p1 = {
		pos = math.floor((grid-1)/2*(grid-1)+(grid-1)*2/3),
		dir = 2
	}
end

function debugs()
	for k,v in pairs(tile) do
		love.graphics.print(k, v.x, v.y)
	end
end

function love.draw()
	if win == 0 then
		for k,v in pairs(tile) do
			if v.on == 1 then
				love.graphics.setColor(255, 0, 0)
			elseif v.on == 2 then
				love.graphics.setColor(0,0,255)
			end
			if v.on ~= 0 then
				love.graphics.rectangle("fill", v.x, v.y, tilesize, tilesize)
			end
		end
	elseif win ~= 0 then
		love.graphics.printf("Player "..win.." wins! \n Press SPACE to play again!", 0, window/2, window, "center" )
	end
end

function love.update()
	for k,v in pairs(control) do
		if love.keyboard.isDown(v[1]) then
			p1.dir = k
		end
		if love.keyboard.isDown(v[2]) then
			p2.dir = k
		end
	end
	if delay <= 0 and win == 0 then
		p1.pos = p1.pos+move[p1.dir]
		p2.pos = p2.pos+move[p2.dir]
		if tile[p1.pos] == nil or tile[p1.pos].on ~= 0 then
			win = 1
		elseif tile[p2.pos] == nil or tile[p2.pos].on ~= 0 then
			win = 2
		end
		for k,v in pairs(tile) do
			if p1.pos == k then
				v.on = 2
			elseif p2.pos == k then
				v.on = 1
			end
		end
		delay = 1
	elseif delay > 0 then
	delay = delay-0.5
	end
	if win ~= 0 and love.keyboard.isDown(" ") then
		love.load()
	end
end