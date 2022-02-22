function init()
   draw.setscreen(1)
   w, h = draw.getport()
   tiles = {}
   xtiles = {}
   ytiles = {}
   setPieces()
   drawBoard()
   sleep(10000)
end

function setPieces()
   for i = 1, 8 do
      tiles[i+8] = {"wP", 1}
      tiles[i+48] = {"bP", 2}
   end
   tiles[1] = {"wR", 1}
   tiles[2] = {"wN", 1}
   tiles[3] = {"wB", 1}
   tiles[4] = {"wQ", 1}
   tiles[5] = {"wK", 1}
   tiles[6] = {"wB", 1}
   tiles[7] = {"wN", 1}
   tiles[8] = {"wR", 1}
   tiles[57] = {"bR", 2}
   tiles[58] = {"bN", 2}
   tiles[59] = {"bB", 2}
   tiles[60] = {"bQ", 2}
   tiles[61] = {"bK", 2}
   tiles[62] = {"bB", 2}
   tiles[63] = {"bN", 2}
   tiles[64] = {"bR", 2}
end

function drawBoard()
   x = 0
   y = w+2*w/8
   for i = 1, 64 do
      draw.rect(x, y, x+w/8, y-w/8, draw.black)
      xtiles[i] = x+w/16
      ytiles[i] = y+w/16
      x = x + w/8
      if i % 8 == 0 then
         y = y - w/8
         x = 0
      end
   end
end

function drawPieces()
for i = 1, 64 do
draw.image("@resources/cleartile.png", xtiles[i], ytiles[i])
end
for k, v in pairs(tiles) do
draw.image("@resources/"..v..".png, xtiles[k], ytiles[k])
end
end

function verifyTap(x, y, x1, y1, x2, y2)
if x >= x1 and x <= x2 and y >= y1 and y <= y2 then
return true
end

function moveRule(p, t)
if p[1] == "wP" then
if t == activetile+8 and t == nil then
return true
elseif t == activetile+9 or t == activetile+7 and tiles[t][2] ~= p[2] then
return true
end
elseif p[1] == "wN" then
if t == activetile 
else
return false
end

function movePiece(i)
if moveRule(tiles[i], i) == true then
tiles[i] = tiles[activetile]
tiles[activetile] = nil
drawPieces()
elseif moveRule(tiles[1], i) == false then
end
end

function checkTap(x, y)
for i = 1, #xtiles do
if verifyTap(x, y, xtiles[i], ytiles[i], xtiles[i]+w/8, ytiles[i]+w/8) == true then
if activetile ~= nil then
movePiece(i)
elseif activetile == nil then
end
end
end


end

function detectTouch()
function started(x, y)
checkTap(x, y)
end
function dragged(x, y)
end
function ended(x, y)
end
draw.tracktouches(started, dragged, ended)
while true do
draw.doevents()
end
end

init()
detectTouch()
