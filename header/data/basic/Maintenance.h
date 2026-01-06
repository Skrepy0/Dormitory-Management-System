#pragma once
#include "../../../source/data/library/json.hpp"
#include "./Time.h"
class Maintenance {
private:
    nlohmann::json data;

    Time reportTime; // 报修时间
    Time repairTime; // 维修时间
    std::string sponsor; // 报修人
    std::string description; // 报修描述
    std::string repairer; // 维修者
    bool state; // 报修状态
    std::string valuation; // 报修评价
    std::string id; // 每个报修的唯一id号码

public:
    static const std::string null;
    Maintenance();
    Maintenance(Time reportTime, Time repairTime, std::string sponsor, std::string description, std::string repairer,
                bool state, std::string valuation, std::string id);

    void updateMaintenance(Time repairTime, std::string repairer, bool state, std::string valuation);

    // getter and setter
    nlohmann::json getMaintenanceData(); // 获取维修记录
    std::string getSponsor();
    std::string getDescription();
    std::string getRepairer();
    std::string getValuation();
    bool getState();
    Time getReportTime(); // 报修时间
    Time getRepairTime(); // 维修时间
    std::string getId();

    void setMaintenanceData(nlohmann::json data); // 获取维修记录
    void setSponsor(std::string sponsor);
    void setDescription(std::string description);
    void setRepairer(std::string repairer);
    void setValuation(std::string valuation);
    void setState(bool state);
    void setReportTime(Time time); // 报修时间
    void setRepairTime(Time time); // 维修时间
};
