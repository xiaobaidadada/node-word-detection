
function abc(){
    const {node_word_detection,get_instance} = require("../src/index");
    node_word_detection.use_sys_sensitive_word();
    console.log(node_word_detection.check_word("傻逼吧"))
    // node_word_detection.add_word("123");
    node_word_detection.add_word("123");
    // node_word_detection.remove_word("123");
    console.log(node_word_detection.get_word_num())
    console.log(node_word_detection.find_word("傻逼123",-1));
    console.log(node_word_detection.find_word("六四天安门事件21312",-1))
    // const abc = get_instance();
    // abc.add_word("123");
    // console.log(abc.check_word("1234"))

    node_word_detection.add_word("刁远萍")
    console.log(node_word_detection.check_word("刁远萍"));
}
abc()