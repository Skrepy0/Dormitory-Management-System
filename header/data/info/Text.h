#pragma once
#include <iostream>
#include "../../../source/data/library/json.hpp"

class Text {
    friend std::ostream &operator<<(std::ostream &out, Text &text);

private:
    std::string path; // json键（需要转化）
    std::string content; // 内容（显示出来的内容）
    std::string language; // 语言
    void init();

    void translate(); // 将path转化成content// to do
    static bool writeLanguageToFile(const std::string &lang);

    nlohmann::json readFromJson();

public:
    Text();

    Text(std::string path);

    static Text
    of(std::string content); // 不通过json直接显示content内容
                             // 用法：Text::of("刘兴康大帅比");可以获得content为"刘兴康大帅比"的Text对象，不通过path转化

    std::string getPath(); // 获取path
    std::string getContent(); // 获取content
    void setPath(std::string path); // 设置path的值
    void setContent(std::string content); // 设置content的值
    static void setLanguage(std::string lang); // 设置语言，lang的值可为"en_us"（英语）、"zh_cn"(中文)
    void addColorCode(std::string colorCode); // 为content添加颜色代码
    Text operator+(Text other); // 重载+运算符，连接两个Text对象的content
    Text &operator=(const Text &other);

    void eraseChar(int index); // 删除content中指定位置的字符
    void eraseChar(int begin, int end); // 删除content中指定范围的字符
    void replaceChar(int index, char c); // 替换content中指定位置的字符

    Text append(Text text);

    static Text intToText(int num);
};

/*  使用参考：
        Text t("test.test");//
   以后写Text的内容时务必写路径，路径（理论上内容随便写）书写要符合规范，
        // 如 用户操作界面/设置/语言设置 处 在写”语言设置“
   的路径时,可以为"screen.operation.option.language_setting"
        // 这样写有层次感~~
        //注意：
   写一个文本时，将路径和内容写在“资源文件/lang/”的两个json文件里面~~

                千万不要在这两个文件里面写注释！
                千万不要在这两个文件里面写注释！
                千万不要在这两个文件里面写注释！

        std::cout << t << std::endl;// 输出内容
        Text::setLanguage("zh_cn");// 设置语言是中文"en_us"
        std::cout << t.getContent() << std::endl;//
   虽然这样写可以不乱码，尽量减少这样写，因为这样写的文本不受语言的影响，中英文都是"刘兴康大帅比"
        t.setPath("test.test01");
        std::cout << t <<std::endl;
*/
