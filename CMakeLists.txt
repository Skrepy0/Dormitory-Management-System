cmake_minimum_required(VERSION 4.0)
project(hnu_dms)

set(CMAKE_CXX_STANDARD 11)

add_executable(hnu_dms main.cpp
        source/data/basic/Dormitory.cpp
        source/data/basic/Maintenance.cpp
        source/data/basic/Time.cpp
        source/data/info/Message.cpp
        source/data/info/Text.cpp
        source/data/library/json.hpp
        source/data/Accommodations.cpp
        source/data/BuildingData.cpp
        source/data/UserData.cpp
        source/data/AdminData.cpp
        source/screen/login/LoginInputMenu.cpp
        source/screen/login/UserLoginInputMenu.cpp
        source/screen/login/LoginSelectMenu.cpp
        source/screen/operation/AdministratorOptions.cpp
        source/screen/operation/UserOptions.cpp
        source/screen/registry/UserRegistryMenu.cpp
        source/screen/SelectMenu.cpp
        source/screen/MenuHelper.cpp
        source/screen/Option.cpp
        source/screen/operation/operations/user/UserApplication.cpp
        source/screen/InputMenu.cpp
        source/data/StayLog.cpp
        source/screen/operation/operations/ChangePassword.cpp
        source/screen/operation/operations/Logout.cpp
        source/screen/operation/operations/SelectLanguage.cpp
        source/screen/login/LoginSelectMenu.cpp
        source/screen/login/LoginInputMenu.cpp
        source/screen/login/UserLogInInputMenu.cpp
        source/screen/operation/operations/administrator/AdminAuditSubMenu.cpp
        source/screen/operation/operations/administrator/AdminDormitoryManagement.cpp
        source/screen/operation/operations/user/UserMaintenance.cpp
        source/screen/operation/operations/user/UserApplication.cpp
        source/screen/operation/AdministratorOperationMenu.cpp
        source/screen/operation/UserOperationMenu.cpp
        source/screen/operation/operations/administrator/DormitoryManageMenu.cpp
        source/screen/operation/operations/user/UserMaintenanceSelectMenu.cpp
        source/screen/operation/operations/administrator/StudentInfoManageMenu.cpp
        source/screen/registry/RegisterInputMenu.cpp
        source/screen/registry/UserRegisterInputMenu.cpp
        source/data/HashHelper.cpp
        header/data/HashHelper.h
        header/data/DataHelper.h
        header/screen/operation/operations/administrator/AdminAccommodationReview.h
        source/screen/operation/operations/administrator/AdminAccommodationReview.cpp
        source/screen/login/AdministratorLoginInputMenu.cpp
        source/screen/operation/operations/administrator/AdminMaintenanceReview.cpp
        header/screen/operation/operations/administrator/AdminMaintenanceReview.h
)
