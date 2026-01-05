#include "../../../header/data/basic/Maintenance.h"
static const std::string null = "maintenance.null";

Maintenance::Maintenance(Time reportTime, Time repairTime, std::string sponsor, std::string description,
                         std::string repairer, bool state, std::string valuation, std::string id) :
    reportTime(reportTime), repairTime(repairTime), sponsor(sponsor), description(description), repairer(repairer),
    state(state), valuation(valuation), id(id) {}

nlohmann::json Maintenance::getMaintenanceData() {
    data["report_time"] = reportTime.getTime();
    data["repair_time"] = repairTime.getTime();
    data["sponsor"] = sponsor;
    data["description"] = description;
    data["repairer"] = repairer;
    data["state"] = state;
    data["valuation"] = valuation;
    data["id"] = id;
    return data;
}

void Maintenance::updateMaintenance(Time repairTime, std::string repairer, bool state, std::string valuation) {
    this->repairTime = repairTime;
    this->repairer = repairer;
    this->state = state;
    this->valuation = valuation;
}

std::string Maintenance::getSponsor() { return sponsor; }

std::string Maintenance::getDescription() { return description; }

std::string Maintenance::getRepairer() { return repairer; }

std::string Maintenance::getValuation() { return valuation; }

bool Maintenance::getState() { return state; }

Time Maintenance::getReportTime() { return reportTime; }

Time Maintenance::getRepairTime() { return repairTime; }

std::string Maintenance::getId() { return id; }

void Maintenance::setMaintenanceData(nlohmann::json data) { this->data = data; }

void Maintenance::setSponsor(std::string sponsor) { this->sponsor = sponsor; }

void Maintenance::setDescription(std::string description) { this->description = description; }

void Maintenance::setRepairer(std::string repairer) { this->repairer = repairer; }

void Maintenance::setValuation(std::string valuation) { this->valuation = valuation; }

void Maintenance::setState(bool state) { this->state = state; }

void Maintenance::setReportTime(Time time) { this->repairTime = time; }

void Maintenance::setRepairTime(Time time) { this->repairTime = time; }
