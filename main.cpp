#include <iostream>
#include <vector>
#include <windows.h>
#include "./header/data/Accommodations.h"
#include "./header/data/BuildingData.h"
#include "./header/data/UserData.h"
#include "./header/data/info/Text.h"
#include "./header/screen/InputMenu.h"
#include "./header/screen/operation/operations/ChangePassword.h"
#include "./header/screen/operation/operations/Logout.h"
#include "./header/screen/operation/operations/user/UserApplication.h"
#include "./header/screen/operation/operations/user/UserMaintenance.h"
#include "header/data/DataHelper.h"
#include "header/data/StayLog.h"
#include "header/data/info/Message.h"
#include "header/screen/Login/UserLoginInputMenu.h"
#include "header/screen/SelectMenu.h"
#include "header/screen/login/AdministratorLoginInputMenu.h"
#include "header/screen/login/LoginSelectMenu.h"
#include "header/screen/operation/operations/administrator/AdminAccommodationReview.h"
#include "header/screen/operation/operations/administrator/AdminDormitoryManagement.h"
#include "header/screen/operation/operations/user/UserApplication.h"
#include "header/screen/operation/operations/user/UserMaintenance.h"
#include "header/screen/registry/UserRegisterInputMenu.h"

int main() {
    LoginSelectMenu menu;
    menu.loop();
    return 0;
}
