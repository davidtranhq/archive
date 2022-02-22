player = {
	tile = 64,
	img = "/images/joemiller.png",
	ctrlkey = {"w", "a", "d", "s"},
	ctrls = {-tilerow, -1, 1, tilerow}, --+2 and =2 to accomodate for nil tiles around map
	range = 2
}

soldier = {
	tile = 15,
	img = "/images/soldier.png",
	ctrlkey = {"w", "a", "d", "s"},
	ctrls = {-tilerow, -1, 1, tilerow},
	range = 2
}