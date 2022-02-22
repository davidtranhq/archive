function detect(s)
for i = s, #message do
let[i] = string.sub(message, i, i)
	for k, v in ipairs(alpha) do
		if let[i] == v then
		inp[i] = k
		elseif let[i] == " " or let[i] == "/n" then
		add = 1
		detect(i+1)
		break
		end
	end
	if inp[i] == nil then
	do return end
	end
	if i%2==0 then
		fin[i] = inp[i]+add
		if inp[i]+add > 26 then
			repeat
			fin[i] = fin[i]-26
			until fin[i] <= 26
		end
		fin[i] = alpha[fin[i]]
	elseif i%2~=0 then
		fin[i] = inp[i]-add
		if inp[i]-add <= 0 then
			repeat
			fin[i] = fin[i]+26
			until fin[i] > 0
		end
		fin[i] = alpha[fin[i]]
	end
	add = add + 1
end
end

repeat 
let = {}
fin = {}
alpha = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"}
inp = {}
add = 1

message = io.read()
detect(1)

for i = #fin, 1, -1 do
io.write(fin[i] or " ")
end
print("\ndecrypt again? (y/n)")
choice = io.read()
until choice == "no"


