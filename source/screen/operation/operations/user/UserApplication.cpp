#include "../../../../../header/screen/operation/operations/user/UserApplication.h"
#include "../../../../../header/data/info/Message.h"
#include "../../../../../header/data/info/Text.h"
#include <stdexcept>
// 获取申请理由（非空+长度限制）
std::string UserApplication::getDormApplyReason() {
    while (true) {
        std::string number =
                getNonEmptyInput("screen.operation.operations.UserApplication.DormApplyReason.Input.number");
        if (number.size() == 12)
            break;
        showError("screen.operation.operations.UserApplication.DormApplyReason.Input.number.error");
        std::cout << std::endl;
    }
    while (true) {
        std::string content;
        content = getNonEmptyInput("screen.operation.operations.UserApplication.DormApplyReason.Input");
        if (content.length() <= 50)
            return content;
        showError("screen.operation.operations.UserApplication.DormApplyReason.Input.error");
        std::cout << std::endl;
    }
}

void UserApplication::inputCheckInApplication() {
    clearScreen();
    showTitle("screen.operation.operations.UserApplication.user.accommodation.checkin.title");
    std::cout << std::endl;
    try {
        std::string userId = getDigitInput(
                "screen.operation.operations.UserApplication.user.accommodation.prompt.user_id",
                1, 12
                );
        std::string userName = getNonEmptyInput(
                "screen.operation.operations.UserApplication.user.accommodation.prompt.user_name");

        json dormInfo = collectDormInfo("screen.operation.operations.UserApplication.user.accommodation.type.checkin");


        std::string reason = getNonEmptyInput(
                "screen.operation.operations.UserApplication.user.accommodation.prompt.reason");

        bool confirm = confirmOperation(
                "screen.operation.operations.UserApplication.user.accommodation.prompt.confirm_submit");
        if (!confirm) {
            showPrompt("screen.operation.operations.UserApplication.user.accommodation.prompt.submit_canceled");
            pause();
            return;
        }


        Time applyTime = Time::getCurrentTime();


        Text typeText("screen.operation.operations.UserApplication.user.accommodation.type.checkin");
        StayLog checkInLog(
                typeText.getContent(),
                applyTime,
                userId,
                userName,
                dormInfo
                );
        json checkInRecord = {
                {"apply_id", generateApplyId(userId)},
                {"apply_time", applyTime.getTime()},
                {"reason", reason},
                {"status", "pending"}
        };


        checkInLog.addCheckInRecords(checkInRecord);
        if (checkInLog.writeToFile()) {
            showSuccess("screen.operation.operations.UserApplication.user.accommodation.checkin.success");
        } else {
            showError("screen.operation.operations.UserApplication.user.accommodation.checkin.error");
        }
    } catch (const std::exception &e) {

        Text errorBase("screen.operation.operations.UserApplication.common.error.apply_failed");
        Text errorContent = errorBase + Text::of(e.what());
        showError(errorContent.getContent());
    }

    pause();
}


void UserApplication::inputCheckOutApplication() {
    clearScreen();
    showTitle("screen.operation.operations.UserApplication.user.accommodation.checkout.title");
    std::cout << std::endl;
    try {
        std::string userId = getDigitInput(
                "screen.operation.operations.UserApplication.user.accommodation.prompt.user_id",
                1, 12
                );
        std::string userName = getNonEmptyInput(
                "screen.operation.operations.UserApplication.user.accommodation.prompt.user_name");
        json dormInfo = collectDormInfo("screen.operation.operations.UserApplication.user.accommodation.type.checkout");
        std::string reason = getNonEmptyInput(
                "screen.operation.operations.UserApplication.user.accommodation.prompt.reason_cancel");

        bool confirm = confirmOperation(
                "screen.operation.operations.UserApplication.user.accommodation.prompt.confirm_submit");
        if (!confirm) {
            showPrompt("screen.operation.operations.UserApplication.user.accommodation.prompt.submit_canceled");
            pause();
            return;
        }

        Time applyTime = Time::getCurrentTime();
        Text typeText("screen.operation.operations.UserApplication.user.accommodation.type.checkout");
        StayLog checkOutLog(
                typeText.getContent(),
                applyTime,
                userId,
                userName,
                dormInfo
                );

        json checkOutRecord = {
                {"apply_id", generateApplyId(userId)},
                {"apply_time", applyTime.getTime()},
                {"reason", reason},
                {"status", "pending"}
        };

        checkOutLog.addCheckOutRecords(checkOutRecord);
        if (checkOutLog.writeToFile()) {
            showSuccess("screen.operation.operations.UserApplication.user.accommodation.checkout.success");
        } else {
            showError("screen.operation.operations.UserApplication.user.accommodation.checkout.error");
        }
    } catch (const std::exception &e) {
        Text errorBase("screen.operation.operations.UserApplication.common.error.apply_failed");
        Text errorContent = errorBase + Text::of(e.what());
        showError(errorContent.getContent());
    }

    pause();
}

json UserApplication::collectDormInfo(const std::string &applyTypeKey) {
    json dormInfo;

    std::string buildingNumKey, roomNumKey, bedNumKey, buildingNameKey;

    if (applyTypeKey == "screen.operation.operations.UserApplication.user.accommodation.type.checkin") {
        buildingNumKey = "screen.operation.operations.UserApplication.user.accommodation.prompt.target_building_number";
        roomNumKey = "screen.operation.operations.UserApplication.user.accommodation.prompt.target_room_number";
        bedNumKey = "screen.operation.operations.UserApplication.user.accommodation.prompt.target_bed_number";
        buildingNameKey = "screen.operation.operations.UserApplication.user.accommodation.prompt.target_building_name";
    } else {
        buildingNumKey =
                "screen.operation.operations.UserApplication.user.accommodation.prompt.current_building_number";
        roomNumKey = "screen.operation.operations.UserApplication.user.accommodation.prompt.current_room_number";
        bedNumKey = "screen.operation.operations.UserApplication.user.accommodation.prompt.current_bed_number";
        buildingNameKey = "screen.operation.operations.UserApplication.user.accommodation.prompt.current_building_name";
    }


    dormInfo["building_number"] = getDigitInput(buildingNumKey, 1, 3);

    dormInfo["room_number"] = getDigitInput(roomNumKey, 3, 4);

    dormInfo["bed_number"] = getDigitInput(bedNumKey, 1, 2);

    dormInfo["building_name"] = getNonEmptyInput(buildingNameKey);

    return dormInfo;
}

std::string UserApplication::generateApplyId(const std::string &userId) {
    Time currentTime = Time::getCurrentTime();
    json timeJson = currentTime.getTime();


    std::string timeStr =
            std::to_string(timeJson["year"].get<int>()) +
            (timeJson["month"].get<int>() < 10 ? "0" : "") + std::to_string(timeJson["month"].get<int>()) +
            (timeJson["day"].get<int>() < 10 ? "0" : "") + std::to_string(timeJson["day"].get<int>()) +
            (timeJson["hour"].get<int>() < 10 ? "0" : "") + std::to_string(timeJson["hour"].get<int>()) +
            (timeJson["minute"].get<int>() < 10 ? "0" : "") + std::to_string(timeJson["minute"].get<int>()) +
            (timeJson["second"].get<int>() < 10 ? "0" : "") + std::to_string(timeJson["second"].get<int>());

    return userId + "_" + timeStr + "_";
}
