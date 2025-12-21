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
        source/menu/login/AdministratorLogInMenu.cpp
        source/menu/login/LogInMenu.cpp
        source/menu/login/UserLogInMenu.cpp
        source/menu/operation/AdministratorOperationMenu.cpp
        source/menu/operation/OperationMenu.cpp
        source/menu/operation/UserOperationMenu.cpp
        source/menu/registry/UserRegistryMenu.cpp
        source/menu/Menu.cpp
        source/menu/MenuHelper.cpp
        source/menu/Option.cpp
        source/data/StayLog.cpp
        header/data/StayLog.h
)
