function tableLength(t, exclude)
	local length = 0
	local excludeStr = ""
	for __, str in pairs(exclude) do
		excludeStr = excludeStr.." "..str
	end
	for k,v in pairs(t) do
		if excludeStr:find(k) == nil then
			length = length+1
		end
	end
	return length
end	


function randomExclude(low,high,exclude_low, exclude_high)
	local var = 0
	repeat var = math.random(low,high) until var > exclude_low or var < exclude_high
	return var
end

function checkBorder(xcrd, ycrd) --x xcrdinate, y xcrdinate
	if xcrd <= border[1].x or ycrd <= border[1].y or ycrd >= border[1].y+border[1].h or xcrd >= border[2].x+border[2].w or ycrd >= border[2].y+border[2].h then
		return false
	elseif xcrd >= border[1].x+border[1].w and xcrd <= border[2].x then
		return false
	else
		return true
	end
end


function checkCollision(x1,y1,w1,h1, x2,y2,w2,h2) --return true if overlap, false if not
	return x1 < x2+w2 and
         x2 < x1+w1 and
         y1 < y2+h2 and
         y2 < y1+h1
end

function shipImpact(e,t)
	if ship[e].health ~= 0 then
		if ship[e].effects.shield > 0 then
			ship[e].effects.shield = 0
			newImpact(ship[e].coord[1],ship[e].coord[2],ship[e].color)
			powerdownSound:play()
		else
			ship[e].health = ship[e].health - 1
			newImpact(ship[e].coord[1],ship[e].coord[2],{255,255,255})
			impactSound:play()
		end
	end
	if ship[e].health == 0 then
		ship[e].dead = true
		game = t
		for i = 1,50 do
			newImpact(ship[e].coord[1], ship[e].coord[2], {255,255,255})
		end
		shipExplosionSound:play()
	end
end

function createDimensions(t)
	local output = {}
	for k,img in pairs(t) do
		output[k] = {}	
		output[k].x = img:getWidth()
		output[k].y = img:getHeight()
		
	end
	return output
end

function newControl(key, crd, val, ship)
	ctrls[key] = {crd = crd, val = val, ship = ship}
end

function newImpact(x,y,c)
	for impactID = 1, #impact+1 do
		if impact[impactID] == nil then
			impact[impactID] = {
				x = x,
				y = y,
				color = c,
				shards = {},
				shardspeed = {},
				life = 60,
			}
			for i = 1,60 do
				impact[impactID].shards[i] = {}
				for ii = 3,5 do
					impact[impactID].shards[i][ii] = impact[impactID].color[ii-2]
				end
				impact[impactID].shardspeed[i] = {}
				for ii = 1,2 do
					impact[impactID].shardspeed[i][ii] = randomExclude(-5,5,0,0)
				end
				if i%2 ~= 0 then
					impact[impactID].shards[i][1] = impact[impactID].x
					impact[impactID].shards[i][2] = impact[impactID].y
				else
					impact[impactID].shards[i][1] = xwindow-impact[impactID].x
					impact[impactID].shards[i][2] = ywindow-impact[impactID].y
				end
			end
			return
		end
	end
end

function newPowerup()
	for ii = 1,2 do
		for i = 1, #powerups + 1 do
			if powerups[i] == nil then
				powerups[i] = {
					x = math.random( border[ii].x, border[ii].x+border[ii].w), --spawn on anyside
					y = math.random( border[ii].y + border[ii].h/2, border[ii].y+border[ii].h), --spawn only on bottom half
					team = ii,
					rot = 0,
				}
				powerups[i].id = powerup_index[math.random(1, tableLength(powerup_list, {"dimen", "img"} ) )]
				if ii == 1 then
					powerups[i].enemy = 2	
				else
					powerups[i].enemy = 1
				end
				break
			end
		end
	end
	newPowerupSound:play()
end




function newStar(i)
	if i%2 ~= 0 then
		stars[i] = math.random(0,xwindow)
	else
		stars[i] = math.random(0,ywindow)
	end	
	starspeed[i] = randomExclude(-2,2,0,0)
end



function newBullet(i,e)
	for bulletID = 1, #bullet+1 do
		if bullet[bulletID] == nil then
			bullet[bulletID] = {
				x = ship[i].coord[1],
				y = ship[i].coord[2],
				team = i,
				enemy = e,
				speed = ship[i].gun,
			}
			ship[i].reloading = 0
			break
		end
	end
end

function newShipEffect(x,y,effect,t)
	for i = 1, #shipEffects + 1 do
		if shipEffects[i] == nil then
			shipEffects[i] = {
				id = effect,
				x = x,
				y = y,
				img = shipEffect_list[effect].img[t],
				rot = 0,
				team = t,
			}
			break
		end
	end
end

function newAsteroid(x,y,s)
	for i = 1, #asteroids + 1 do
		if asteroids[i] == nil then
			asteroids[i] = {
				size = s,
				img = math.random(1,3),
				health = math.random(1,3)*s,
				speed = {randomExclude(-3,3,0,0)/math.random(1,2), randomExclude(-3,3,0,0)/math.random(1,2)},
				rot = math.random(0,math.pi*2),
				x = x,
				y = y,
			}
			break
		end
	end
end

function loadShips()
	ship = {}
	bullet = {}
	impact = {}
	powerups = {}
	shipEffects = {}
	for i = 1,2 do
		ship[i] = {
			maxspd = 50,
			dead = false,
			acc = 2,
			speed = {0,0},
			gun = 5, --bullet speed
			reload = 20,
			reloading = 20,
			health = 20,
			maxhp = 20,
			coord = {0, 500},
			effects = {shield = 0, reload = 0, speed = 0},
			img_ship = love.graphics.newImage("res/graphics/ship"..i..".png"),
			img_bullet = love.graphics.newImage("res/graphics/bullet"..i..".png"),
			score = 0
		}
		ship[i].dimen = {
			ship = {x = ship[i].img_ship:getWidth(), y = ship[i].img_ship:getHeight()},
			bullet = {x = ship[i].img_bullet:getWidth(), y = ship[i].img_ship:getHeight()},
		}
	end
	ship[1].coord[1] = xwindow/4
	ship[2].coord[1] = 3*xwindow/4
	ship[1].color = {255,0,0}
	ship[2].color = {200,200,255}
end

function loadHUD()
	bar_health = {}
	for i = 1,2 do
		bar_health[i] = {
			x = border[i].x + xwindow/20,
			y = border[i].y + border[i].h + ywindow/100,
			w = border[i].w/2,
			h = (ywindow-border[i].h)/2 - ywindow/50,
		}
	end
end

function loadControls()
	ctrls = {}
	newControl('w', 2, -1, 1)
	newControl('a', 1, -1, 1)
	newControl('s', 2, 1, 1)
	newControl('d', 1, 1, 1)
	newControl('up', 2, -1, 2)
	newControl('left', 1,-1,2)
	newControl('down', 2,1,2)
	newControl('right', 1,1,2)
end

function loadScene()
	stars = {}
	starspeed = {}
	for i = 1, 300 do
		newStar(i)
	end
	border = {}
		border[1] = {
			x = xwindow/50,
			y = ywindow/30,
			w = 23*xwindow/50,
			h = 28*ywindow/30,
		}
		border[2] = {
			x = xwindow*26/50,
			y = ywindow/30,
			w = 23*xwindow/50,
			h = 28*ywindow/30,
		}
	divide = {
		{x = border[1].x, y = (border[1].y+border[1].h)/2},
		{x = border[2].x, y = (border[2].y+border[2].h)/2},
	}
end

function loadPowerups()
	powerup_list = {
		maxhp = {	
			img = love.graphics.newImage("res/graphics/plus.png"),
			effect = function(i)
				ship[i].maxhp = ship[i].maxhp + 5
				ship[i].health = ship[i].health + 5
			end,
		},
		heal = {
			img = love.graphics.newImage("res/graphics/heart.png"),
			effect = function(i)
				ship[i].health = ship[i].health + 20
				if ship[i].health > ship[i].maxhp then
					ship[i].health = ship[i].maxhp
				end
			end,
		},
		shield = {
			img = love.graphics.newImage("res/graphics/shield.png"),
			duration = 1200,
			effect = function(i)
				ship[i].effects.shield = 600
				newShipEffect(ship[i].coord[1], ship[i].coord[2], "shield", i)
			end,
			negate = function(i)
			end,
		},
		reload = {
			img = love.graphics.newImage("res/graphics/reload.png"),
			duration = 600,
			effect = function(i)
				ship[i].effects.reload = 600
				ship[i].reload = ship[i].reload/2
				ship[i].reloading = ship[i].reload
			end,
			negate = function(i)
				ship[i].reload = ship[i].reload*2
				ship[i].reloading = ship[i].reload
			end,
		},
		speed = {
			img = love.graphics.newImage("res/graphics/timer.png"),
			duration = 600,
			effect = function(i)
				ship[i].effects.speed = 600
				ship[i].maxspd = ship[i].maxspd*2
				ship[i].acc = ship[i].acc*2
			end,
			negate = function(i)
				ship[i].maxspd = ship[i].maxspd/2
				ship[i].acc = ship[i].acc/2
			end,
		},
		img = {love.graphics.newImage("res/graphics/red_powerup.png"), love.graphics.newImage("res/graphics/blue_powerup.png")},
	}
	powerup_index = {"shield", "maxhp", "heal", "reload", "speed"}
	powerup_list.dimen = createDimensions(powerup_list.img)
end

function loadShipEffects()
	shipEffect_list = {
		shield = {
			img = {love.graphics.newImage("res/graphics/red_barrier.png"), love.graphics.newImage("res/graphics/blue_barrier.png")},
		}
	}
	shipEffect_list.shield.dimen = createDimensions(shipEffect_list.shield.img)
end

function loadAsteroids()
	asteroids = {}
	asteroid_img = {love.graphics.newImage("res/graphics/asteroid1.png"), love.graphics.newImage("res/graphics/asteroid2.png"), love.graphics.newImage("res/graphics/asteroid3.png")}
	asteroid_dimen = createDimensions(asteroid_img)
end

function loadEndGame()
	endGame = {
		dimen = {x=2*xwindow/5, y=3*ywindow/5, w=xwindow/5, h=ywindow/10}
	}
end

function drawShips()
	for i = 1,2 do
		if ship[i].dead == false then
			love.graphics.draw(ship[i].img_ship, ship[i].coord[1], ship[i].coord[2], 0, 1,1, ship[i].dimen.ship.x/2, ship[i].dimen.ship.y/2)
			love.graphics.draw(ship[i].img_ship, xwindow-ship[i].coord[1], ywindow-ship[i].coord[2], math.pi, 1,1, ship[i].dimen.ship.x/2, ship[i].dimen.ship.y/2)
		end
	end
end

function drawBullet()
	for k,v in pairs(bullet) do
		love.graphics.draw(ship[v.team].img_bullet, v.x, v.y, 0, 1,1, ship[v.team].dimen.bullet.x/2, ship[v.team].dimen.bullet.y/2)
		love.graphics.draw(ship[v.team].img_bullet, xwindow-v.x, ywindow-v.y, math.pi, 1,1, ship[v.team].dimen.bullet.x/2, ship[v.team].dimen.bullet.y/2)
	end
end

function drawImpact()
	for k,v in pairs(impact) do
		love.graphics.points(v.shards)
	end
end

function drawBorder()
	for i = 1,2 do
		love.graphics.rectangle("line", border[i].x, border[i].y, border[i].w, border[i].h)
	end
end

function drawScene()
	love.graphics.points(stars)
end

function drawHUD()
	love.graphics.setFont(gameFont)
	for i = 1,2 do
		if ship[i] then
			love.graphics.setColor(0,255,0)
			love.graphics.rectangle("fill", bar_health[i].x, bar_health[i].y, ship[i].health/ship[i].maxhp*bar_health[i].w, bar_health[i].h )
			love.graphics.setColor(255,255,255)
			love.graphics.rectangle("line", bar_health[i].x, bar_health[i].y, bar_health[i].w, bar_health[i].h )
			love.graphics.print(ship[i].health.."/"..ship[i].maxhp, bar_health[i].x+bar_health[i].w+xwindow/200, bar_health[i].y-ywindow/100)
			love.graphics.print("P"..i, border[i].x, bar_health[i].y-ywindow/100)
		end
	end
end

function drawPowerups()
	for k,v in pairs(powerups) do
		love.graphics.draw(powerup_list.img[v.team], v.x, v.y, v.rot, 1,1, powerup_list.dimen[1].x / 2, powerup_list.dimen[2].y / 2)
		love.graphics.draw(powerup_list[v.id].img, v.x, v.y, 0, 1,1, powerup_list.dimen[v.team].x / 2, powerup_list.dimen[v.team].y / 2)
		
		love.graphics.draw(powerup_list.img[v.team], xwindow-v.x, ywindow-v.y, v.rot, 1,1, powerup_list.dimen[1].x / 2, powerup_list.dimen[2].y / 2)
		love.graphics.draw(powerup_list[v.id].img, xwindow-v.x, ywindow-v.y, 0, 1,1, powerup_list.dimen[v.team].x / 2, powerup_list.dimen[v.team].y / 2)
	end
end

function drawShipEffects()
	for k,v in pairs(shipEffects) do
		if ship[v.team].effects[v.id] > 0 then
			love.graphics.draw(v.img, v.x, v.y, v.rot, 1,1, shipEffect_list[v.id].dimen[v.team].x/2, shipEffect_list[v.id].dimen[v.team].y/2)
			love.graphics.draw(v.img, xwindow-v.x, ywindow-v.y, v.rot, 1,1, shipEffect_list[v.id].dimen[v.team].x/2, shipEffect_list[v.id].dimen[v.team].y/2)
		end
	end
end

function drawAsteroids()
	for k,v in pairs(asteroids) do
		love.graphics.draw(asteroid_img[v.img], v.x, v.y, v.rot, v.size/3, v.size/3, asteroid_dimen[v.img].x/2, asteroid_dimen[v.img].y/2)
		love.graphics.draw(asteroid_img[v.img], xwindow-v.x, ywindow-v.y, v.rot, v.size/3, v.size/3, asteroid_dimen[v.img].x/2, asteroid_dimen[v.img].y/2)
	end
end

function drawEndGame()
	love.graphics.printf( {ship[game].color,"Winner! \n Press SPACE to play again! \n Press ESC to quit."}, border[game].x, border[game].y+border[game].h/2, border[game].w, "center" )
end

function accelerateShip()
	for k,v in pairs(ctrls) do
		if love.keyboard.isDown(k) then
			ship[v.ship].speed[v.crd] = ship[v.ship].speed[v.crd] + ship[v.ship].acc * v.val
		end
	end
end

function moveShip()
	for i = 1,2 do
		for ii = 1,2 do
		
			if ship[i].speed[ii] >= ship[i].maxspd then
				ship[i].speed[ii] = ship[i].maxspd
			elseif ship[i].speed[ii] <= -ship[i].maxspd then
				ship[i].speed[ii] = -ship[i].maxspd
			end --regulate maxspeed
			
			if ship[i].speed[ii] > 0 then
				ship[i].speed[ii] = ship[i].speed[ii]-ship[i].acc/2
			elseif ship[i].speed[ii] < 0 then
				ship[i].speed[ii] = ship[i].speed[ii]+ship[i].acc/2
			end --regulate deceleration
			
			if checkBorder( ship[i].coord[1] + ship[i].speed[1]/10 , ship[i].coord[2] + ship[i].speed[2]/10) and 
			checkCollision( ship[i].coord[1] - ship[i].dimen.ship.x/2 + ship[i].speed[1]/10, ship[i].coord[2] - ship[i].dimen.ship.y/2 + ship[i].speed[2]/10, ship[i].dimen.ship.x, ship[i].dimen.ship.y, divide[i].x, divide[i].y, border[i].w, 0) == false then --if ship will move to blocked path, don't allow
				ship[i].coord[ii] = ship[i].coord[ii] + ship[i].speed[ii]/10
			else
			end
		end
	end
end

function fireShip()
	if love.keyboard.isDown("lshift") and ship[1].reloading == ship[1].reload then
		newBullet(1,2)
		pewSound:play()
	end
	if love.keyboard.isDown("rctrl") and ship[2].reloading == ship[2].reload then
		newBullet(2,1)
		pewSound:play()
	end
	for i = 1,2 do
		if ship[i].reloading < ship[i].reload then
			ship[i].reloading = ship[i].reloading + 1
		end
		if ship[i].reloading > ship[i].reload then
			ship[i].reloading = ship[i].reload
		end
	end
end
 
function updateShips()
	accelerateShip()
	moveShip()
	fireShip()
end

function updateBullet()
	for k,v in pairs(bullet) do
		if v ~= nil then
			for kk,vv in pairs(bullet) do
				if checkCollision(v.x, v.y - v.speed, ship[v.team].dimen.bullet.x, ship[v.team].dimen.bullet.y, xwindow-vv.x, ywindow-vv.y - vv.speed, ship[vv.team].dimen.bullet.x, ship[vv.team].dimen.bullet.y) and v.team ~= vv.team then
					newImpact(v.x,v.y,ship[v.team].color)
					newImpact(vv.x,vv.y,ship[vv.team].color)
					bullet[k] = nil
					bullet[kk] = nil
					metalSound:play()
				end
			end
			if checkBorder(v.x, v.y - v.speed) == false then
				newImpact(v.x, v.y, ship[v.team].color)
				bullet[k] = nil
				metalSound:play()
			elseif checkCollision(v.x, v.y - v.speed, ship[v.team].dimen.bullet.x, ship[v.team].dimen.bullet.y, xwindow-ship[v.enemy].coord[1]-ship[v.enemy].dimen.ship.x/2, ywindow-ship[v.enemy].coord[2]-ship[v.enemy].dimen.ship.y/2, ship[v.enemy].dimen.ship.x, ship[v.enemy].dimen.ship.y) then
				shipImpact(v.enemy, v.team)
				newImpact(v.x, v.y, ship[v.team].color)
				bullet[k] = nil
			else
				v.y = v.y - v.speed
			end --collisions
			
		end
	end
end

function updateScene()
	for k,v in pairs(starspeed) do
		stars[k] = stars[k] + v
		if k%2 ~= 0 and stars[k] > xwindow or stars[k] < 0 then
			newStar(k)
		elseif k%2 == 0 and stars[k] > ywindow or stars[k] < 0 then
			newStar(k)
		end
	end
end

function updateImpact()
	for impactID,t in pairs(impact) do
		for shard,speed in pairs(t.shardspeed) do
			for i = 1,2 do
				t.shards[shard][i] = t.shards[shard][i] + speed[i]
			end
		end
		if t.life == 0 then
			impact[impactID] = nil
		else
			t.life = t.life-1
		end
	end
end

function updatePowerups()
	if math.random(1,500) == 1 then
		newPowerup()
	end
	for	k, t in pairs(powerups) do
		if checkCollision(t.x - powerup_list.dimen[t.team].x / 2, t.y - powerup_list.dimen[t.team].y/2, powerup_list.dimen[t.team].x, powerup_list.dimen[t.team].y, ship[t.team].coord[1] - ship[t.team].dimen.ship.x/2, ship[t.team].coord[2] - ship[t.team].dimen.ship.y/2, ship[t.team].dimen.ship.x, ship[t.team].dimen.ship.y ) then
			powerup_list[t.id].effect(t.team)
			powerups[k] = nil
			powerupSound:play()
		end
		for bulletID,v in pairs(bullet) do
			if v.enemy == t.team then
				if checkCollision(xwindow - (t.x + powerup_list.dimen[t.team].x / 2), ywindow-(t.y + powerup_list.dimen[t.team].y/2), powerup_list.dimen[t.team].x, powerup_list.dimen[t.team].y, v.x - ship[t.enemy].dimen.bullet.x / 2, v.y - ship[t.enemy].dimen.bullet.y / 2, ship[t.enemy].dimen.bullet.x, ship[t.enemy].dimen.bullet.y) then
					powerups[k] = nil
					bullet[bulletID] = nil
					newImpact(t.x, t.y, ship[t.enemy].color)
					metalSound:play()
				end
			end
		end
		t.rot = t.rot - 1
	end
end

function updateShipEffects()
	for i = 1,2 do
		if ship[i] then
			for k,v in pairs(ship[i].effects) do
				if v ~= 0 then
					ship[i].effects[k] = ship[i].effects[k] - 1
				end
			end
		end
	end
	
	for k,v in pairs(shipEffects) do
		v.rot = v.rot + 1
		v.x = ship[v.team].coord[1]
		v.y = ship[v.team].coord[2]
		
	end

	for i = 1,2 do
		for k,effect in pairs(ship[i].effects) do
			if effect == 1 then
				powerup_list[k].negate(i)
			end
		end
	end
end

function updateAsteroids()
	if math.random(1,1200) == 1 then
		newAsteroid(math.random(border[1].x, border[1].x+border[1].w), math.random(border[1].y+border[1].h/2, border[1].y+border[1].h), math.random(1,3))
	end
	if timer == 1 then
		local rdm = math.random(1,3)
		newAsteroid(math.random(border[1].x+asteroid_dimen[rdm].x, border[1].x+border[1].w-asteroid_dimen[rdm].x), math.random(border[1].y+border[1].h/2+asteroid_dimen[rdm].y, border[1].y+border[1].h-asteroid_dimen[rdm].y), rdm)
	end
	for k,v in pairs(asteroids) do
		v.x = v.x+v.speed[1]
		v.y = v.y+v.speed[2]
		
		if v.x-asteroid_dimen[v.img].x/2/3*v.size <= border[1].x or v.x+asteroid_dimen[v.img].x/2/3*v.size >= border[1].x+border[1].w then
			v.speed[1] = -v.speed[1]
		end
		if v.y-asteroid_dimen[v.img].y/2/3*v.size <= border[1].y or v.y+asteroid_dimen[v.img].y/2/3*v.size >= border[1].y+border[1].h then
			v.speed[2] = -v.speed[2]
		end
		
		for kk,vv in pairs(bullet) do
			if checkCollision(v.x-asteroid_dimen[v.img].x/2/3*v.size, v.y-asteroid_dimen[v.img].x/2/3*v.size, asteroid_dimen[v.img].x/3*v.size, asteroid_dimen[v.img].y/3*v.size, vv.x, vv.y, ship[vv.team].dimen.bullet.x, ship[vv.team].dimen.bullet.y) 
			or checkCollision(v.x-asteroid_dimen[v.img].x/2/3*v.size, v.y-asteroid_dimen[v.img].x/2/3*v.size, asteroid_dimen[v.img].x/3*v.size, asteroid_dimen[v.img].y/3*v.size, xwindow-vv.x, ywindow-vv.y, ship[vv.team].dimen.bullet.x, ship[vv.team].dimen.bullet.y) then
				v.health = v.health-1
				newImpact(vv.x, vv.y, ship[vv.team].color)
				bullet[kk] = nil
				metalSound:play()
			end
		end
		
		if v.health <= 0 then
			asteroids[k] = nil
			if v.size ~= 1 then
				for i = 1,4 do
					newAsteroid(v.x,v.y,v.size-1)
				end
			end
		end
			
		
		
		if checkCollision(v.x-asteroid_dimen[v.img].x/2/3*v.size, v.y-asteroid_dimen[v.img].x/2/3*v.size, asteroid_dimen[v.img].x/3*v.size, asteroid_dimen[v.img].y/3*v.size, ship[1].coord[1], ship[1].coord[2], ship[1].dimen.ship.x, ship[1].dimen.ship.y) then
			shipImpact(1,2)
			v.speed[1] = -v.speed[1]
			v.speed[2] = -v.speed[2]
		end
		if checkCollision(v.x-asteroid_dimen[v.img].x/2/3*v.size, v.y-asteroid_dimen[v.img].x/2/3*v.size, asteroid_dimen[v.img].x/3*v.size, asteroid_dimen[v.img].y/3*v.size, xwindow-ship[2].coord[1], ywindow-ship[2].coord[2], ship[2].dimen.ship.x, ship[2].dimen.ship.y) then
			shipImpact(2,1)
			v.speed[1] = -v.speed[1]
			v.speed[2] = -v.speed[2]
		end
	end
end

function updateEndGame()
	if love.keyboard.isDown("space") then
		love.load()
	elseif love.keyboard.isDown("esc") then
		os.exit()
	end
end

function loadHelp()
	helpText = {
		{text = "Welcome to ASTRO BLASTER!", side = 1, fade = 60, alpha = 0, start = 0, finish = 180},
		{text = "The goal of the game is to", side = 1, fade = 60, alpha = 0, start = 180, finish = 360},
		{text = "destroy your opponent's ship!", side = 2, fade = 60, alpha = 0, start = 180, finish = 360},
		{text = "This is PLAYER ONE's side.", side = 1, fade = 60, alpha = 0, start = 360, finish = 540},
		{text = "This is PLAYER TWO's side.", side = 2, fade = 60, alpha = 0, start = 540, finish = 720},
		{text = "Use WASD to move, and LSHIFT to shoot.", side = 1, fade = 60, alpha = 0, start = 720, finish = 900},
		{text = "Use ARROWS to move and RCTRL to shoot.", side = 2, fade = 60, alpha = 0, start = 900, finish = 1080},
		{text = "Collect powerups of your color...", side = 1, fade = 60, alpha = 0, start = 1080, finish = 1260},
		{text = "...and shoot those of your opponent's!", side = 2, fade = 60, alpha = 0, start = 1260, finish = 1440},
		{text = "Dodge and destroy asteroids...", side = 1, fade = 60, alpha = 0, start = 1440, finish = 1620},
		{text = "..or be destroyed!", side = 2, fade = 60, alpha = 0, start = 1620, finish = 1800},
	}
end

function drawHelp()
	for k,v in pairs(helpText) do
		if timer >= v.start and timer <= v.finish then
			love.graphics.printf({ {255,255,255,v.alpha}, v.text}, border[v.side].x, (border[v.side].y+border[v.side].h)/2, border[v.side].w, "center")
		end
	end
end

function updateHelp()
	for k,v in pairs(helpText) do
		if timer >= v.start and timer < v.start+v.fade then
			v.alpha = v.alpha + 255/v.fade
		elseif timer <= v.finish and timer > v.finish-v.fade then
			v.alpha = v.alpha-255/v.fade
		end
	end
	if timer == 2000 then
		game = 3
	end
end

function loadStart()
	start_asteroid = {}
	choice = {
		play = {
			x = xwindow/5,
			y = ywindow*4/5,
			text = "PLAY"
		},
		help = {
			x = xwindow*3/5,
			y = ywindow*4/5,
			text = "HELP"
		}
	}
	choose = "play"
end

function startAsteroid()
	for i = 1, #start_asteroid+1 do
		if start_asteroid[i] == nil then
			start_asteroid[i] = {
				x = 0,
				y = 0,
				img = math.random(1,3),
				size = math.random(1,3),
				speed = {math.random(1,3), math.random(1,3)},
				rot = math.random(0, math.pi*2)
			}
			break
		end
	end
end

function drawStart()
	love.graphics.setFont(titleFont)
	love.graphics.printf("ASTRO BLASTER", xwindow/5, ywindow/10, xwindow*3/5, "left")
	love.graphics.draw(ship[1].img_ship, xwindow*2.9/5, ywindow/7, math.pi*7.5/4, 3,3, ship[1].dimen.ship.x/2, ship[1].dimen.ship.y/2)
	love.graphics.draw(ship[2].img_ship, xwindow*3.5/5, ywindow/4.5, math.pi*7.5/4, 3,3, ship[2].dimen.ship.x/2, ship[2].dimen.ship.y/2)
	love.graphics.setFont(love.graphics.newFont(12))
	love.graphics.printf("v1.0 ©HydratedVeggies", 0, ywindow-12, xwindow, "right")
	love.graphics.setFont(helpFont)
	for k,v in pairs(choice) do
		if k == choose then
			love.graphics.printf(">"..v.text.."<", v.x, v.y, helpFont:getWidth(">"..v.text.."<"), "center")
		else
			love.graphics.printf(v.text, v.x, v.y, helpFont:getWidth(v.text), "center")
		end
	end
	for k,v in pairs(start_asteroid) do
		love.graphics.draw(asteroid_img[v.img], v.x, v.y, v.rot, v.size/3, v.size/3)
	end
end

function updateStart()
	if math.random(1,300) == 1 then
		startAsteroid()
	end
	for k,v in pairs(start_asteroid) do
		v.x = v.x+v.speed[1]
		v.y = v.y+v.speed[2]
		if v.x > xwindow or v.y > ywindow then
			start_asteroid[k] = nil
		end
	end
	if love.keyboard.isDown("left") then
		love.audio.play(boopSound)
		choose = "play"
	elseif love.keyboard.isDown("right") then
		love.audio.play(boopSound)
		choose = "help"
	end
	if love.keyboard.isDown("return") then
		if choose == "play" then
			game = 0
			timer = 0
			ship[1].health = 20
			ship[2].health = 20
		elseif choose == "help" then
			game = 4
			timer = 0
		end
		love.audio.play(boopSound)
	end
end

function drawCountDown()
	love.graphics.setFont(titleFont)
	love.graphics.print(countCount, xwindow/2, ywindow/2, 0, countSize)
end

function updateCountDown()
	if timer == 60 then
		countCount = 2
	elseif timer == 120 then
		countCount = 1
	elseif timer == 180 then
		countCount = "GO!"
	end
	if countSize > 1 then
		countSize = countSize - 1
	elseif countSize <= 1 then
		countSize = 60
	end
end

function drawAbout()
	local about = [[
	ASTRO BARRIER v1.0, 2016
	Design - David Tran
	Programming - David Tran
	Art - David Tran
	Music - Allan Haapalainen, A Journey Through Space
	]]
	love.graphics.setFont(helpFont)
	love.graphics.printf(about, 0,0,xwindow,"center")
end

function love.load()
	math.randomseed( os.time() )
	math.random() math.random() math.random()
	xwindow, ywindow = 900, 600
	game = 3
	countSize = 60
	countCount = 3
	love.window.setMode(xwindow,ywindow)
	love.window.setTitle("Astro Blaster")
	love.window.setIcon(love.image.newImageData("icon.png"))
	timer = 1
	titleFont = love.graphics.newFont("res/font/space_age/space age.ttf", 64)
	helpFont = love.graphics.newFont("res/font/space_age/space age.ttf", 32)
	gameFont = love.graphics.newFont("res/font/space_age/space age.ttf", 24)
	startMusic = love.audio.newSource("res/audio/start.ogg", "stream")
	gameMusic = love.audio.newSource("res/audio/game.ogg", "stream")
	pewSound = love.audio.newSource("res/audio/pew.ogg", "static")
	boopSound = love.audio.newSource("res/audio/boop.ogg", "static")
	impactSound = love.audio.newSource("res/audio/impact.ogg", "static")
	metalSound = love.audio.newSource("res/audio/metal.ogg", "static")
	powerupSound = love.audio.newSource("res/audio/powerup.ogg", "static")
	newPowerupSound = love.audio.newSource("res/audio/newPowerup.ogg", "static")
	shipExplosionSound = love.audio.newSource("res/audio/explosion.ogg", "static")
	powerdownSound = love.audio.newSource("res/audio/powerdown.ogg", "static")
	love.graphics.setFont(titleFont)
	loadStart()
	loadShips()
	loadScene()
	loadControls()
	loadHUD()
	loadPowerups()
	loadShipEffects()
	loadAsteroids()
	loadEndGame()
	loadHelp()
end

function love.draw()
	if game == 3 then
		drawStart()
		drawScene()
	elseif game == 4 then
		drawBorder()
		drawShips()
		drawScene()
		drawHelp()
		drawBullet()
		drawImpact()
	elseif game == 0 then
		love.graphics.setFont(gameFont)
		--[[if timer < 240 then
			drawCountDown()
		end]]
		drawBorder()
		drawShips()
		drawScene()
		drawBullet()
		drawPowerups()
		drawImpact()
		drawShipEffects()
		drawHUD()
		drawAsteroids()
	elseif game == 1 or game == 2 then
		drawBorder()
		drawShips()
		drawScene()
		drawBullet()
		drawPowerups()
		drawImpact()
		drawShipEffects()
		drawHUD()
		drawAsteroids()
		drawEndGame()
	end
end

function love.update()
	if game == 3 then
		love.audio.stop(gameMusic)
		love.audio.play(startMusic)
		updateStart()
		updateScene()
	elseif game == 0 then
		love.audio.stop(startMusic)
		love.audio.play(gameMusic)
		--if timer < 240 then
			--updateCountDown()
		--else
		updateScene()
		updateImpact()
		updateShips()
		updateBullet()
		updatePowerups()
		updateShipEffects()
		updateAsteroids()
		--end
	elseif game == 4 then
		ship[1].health = 100000
		ship[2].health = 100000
		updateScene()
		updateShips()
		updateHelp()
		updateBullet()
		updateImpact()
	elseif game == 1 or game == 2 then
		love.audio.stop(gameMusic)
		updateEndGame()
		updateScene()
		updateImpact()
	end
	timer = timer + 1
end

function love.keypressed(k)
	if k == "escape" then
		love.audio.stop(gameMusic)
		love.audio.stop(startMusic)
		love.load()
	end
end