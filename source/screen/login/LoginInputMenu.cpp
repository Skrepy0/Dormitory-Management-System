#include "../../../header/screen/Login/LoginInputMenu.h"

bool LoginInputMenu::login(std::string &key, std::string &prompt) {
    const int maxRetry = 3;
    int retryCount = 0;

    while (retryCount < maxRetry) {
        if (Logout::checkEscKey()) {
            clearScreen();
            showContent("screen.login.LoginScreen.login.cancel");
            return false;
        }
        std::string id = getDigitInput(prompt, 12,12 // 假设学号是8位，限制长度8-8
        );


        if (Logout::checkEscKey()) {
            clearScreen();
            showContent("screen.login.LoginScreen.login.cancel");
            return false;
        }
        std::string pwd = getNonEmptyInput("screen.login.LoginScreen.login.password");

        if (Logout::checkEscKey()) {
            clearScreen();
            showContent("screen.login.LoginScreen.login.cancel");
            return false;
        }

        if (verifyCredentials(id, pwd)) {
            clearScreen();
            showSuccess("screen.login.LoginScreen.login.success");
            key = id;
            return true;
        } else {
            retryCount++;
            showError("screen.login.LoginScreen.login.fail");


            if (retryCount < maxRetry) {
                showPrompt("screen.login.LoginScreen.login.try");
                showContent(std::to_string(maxRetry - retryCount));
            }
        }
    }

    clearScreen();
    showError("screen.operation.operations.UserLogin.login.max_retry");
    return false;
}
