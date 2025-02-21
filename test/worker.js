console.log('子线程')
const node_word_detection= require("../build/Debug/node-word-detection");
require("../build/Debug/node-word-detection");
node_word_detection.add_word("测试啊");
// node_word_detection.remove_word("测试啊")
// node_word_detection.add_word("测试啊");
console.log(node_word_detection.check_word("测试啊"));
console.log(node_word_detection.get_word_num())
