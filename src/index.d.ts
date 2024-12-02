interface check_result {
    have: boolean;
    str: string;
}

export interface node_word_detection {

    /**
     *  add a word : exp test abc
     *  添加一个单词 比如 傻逼 这样的敏感词
     * @param word
     */
    add_word: (word: string) => void;

    /**
     * checks whether a word in a sentence functions
     * 检查这个句子中是否有 某个单词 敏感词
     * @param text
     */
    check_word: (text: string) => boolean;

    /**
     * 检测同步替换全部字符串
     */
    check_word_replace: (text: string, replace_str: string) => check_result;

    /**
     * 查找违禁词
     * @param text
     * @param num -1是查找全部
     */
    find_word(text: string, num: number): string[];

    /**
     * 查找并替换违禁词
     * @param text
     * @param num -1是查找全部
     * @param replace_str
     */
    find_word_replace(text: string, num: number,replace_str: string): {list:string[] ,str:string};
}

export declare const node_word_detection: node_word_detection;