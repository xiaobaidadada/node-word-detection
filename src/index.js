
const word_detection = require("../build/Release/word-detection.node")


word_detection.add_word("123");
console.log(word_detection.check_word("0h78123njn"));