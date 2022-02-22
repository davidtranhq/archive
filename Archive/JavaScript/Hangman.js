var replaceChar = function(index, replace) {
	uncovered = this.substr(0,index) + replace + this.substr(index,uncovered.length);
}
var lives = 10;
var guessed = "";
var uncovered = "";
var correct = false
var win = false;

while(win===false) {
	var word.toLowerCase() = prompt("Choose a word for your friend to guess!");

	for (i=0;i<=word.length;i++) {
		uncovered += "#";
	};

	clear();
	var guess.toLowerCase() = prompt("Guess a letter! You have "+lives+" left. You have uncovered: "+uncovered+" . You have guessed: "+guessed);

	for (i=0;i<=word.length;i++) {
		if (guess === word[i]) {
			uncovered.replaceChar(i, guess);
			correct = true
		};
	};
	if (correct === false) {
		lives -= 1;
	};
	guessed += guess
	correct = false
}