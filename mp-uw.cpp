#include <windows.h>
#include <string>
#include <iostream>

bool starts_with(const std::string& fullString, const std::string& prefix) {
    return fullString.compare(0, prefix.size(), prefix) == 0;
}

int main(int argc, char* argv[]) {
    std::string title;
    std::string text;
    std::string type = "none"; // 
    bool parsingTitle = false; // 

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (starts_with(arg, "--title=")) {
            title = arg.substr(8);
            parsingTitle = true;
        } else if (starts_with(arg, "--text=")) {
            text = arg.substr(7);
            parsingTitle = false;
        } else if (starts_with(arg, "--type=")) {
            type = arg.substr(7);
        } else {
            if (parsingTitle) {
                title += " " + arg;
            } else {
                text += " " + arg;
            }
        }
    }

    UINT typeFlag = MB_OK; // 默认
    if (type == "error") {
        typeFlag |= MB_ICONERROR; // 错误类型
    } else if (type == "warning") {
        typeFlag |= MB_ICONWARNING; // 警告类型
    } else if (type == "info") {
        typeFlag |= MB_ICONINFORMATION; // 信息类型
    }

    // Windows API弹出消息框
    MessageBoxA(nullptr, text.c_str(), title.c_str(), typeFlag);

    return 0;
}
